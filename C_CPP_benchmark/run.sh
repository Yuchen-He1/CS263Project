#!/bin/bash
# run_benchmarks.sh
# 并发运行 bin/ 目录下所有 benchmark（C/CPP 的 native 与 WASM 版本），
# 每个 benchmark 运行多次后取平均值，并将结果写入 CSV 文件（results.csv）。
# WASM 版本使用绝对路径调用 wasmtime。

# 设置每个 benchmark 运行次数
NUM_RUNS=5

# WASMTIME 的绝对路径，请根据实际情况修改
WASMTIME="/home/hylanc/.wasmtime/bin/wasmtime"

# CSV 输出文件
CSV_FILE="results.csv"

# 初始化 CSV 文件（写入表头）
echo "Benchmark,Variant,AverageTime(s)" > "$CSV_FILE"

# 定义四种类型对应的后缀和运行命令（native 直接运行，wasm 使用 wasmtime）
declare -A VARIANT_SUFFIX
declare -A VARIANT_CMD
VARIANT_SUFFIX["C_native"]="_c_native.out"
VARIANT_SUFFIX["C_wasm"]="_c_wasm.wasm"
VARIANT_SUFFIX["CPP_native"]="_cpp_native.out"
VARIANT_SUFFIX["CPP_wasm"]="_cpp_wasm.wasm"

VARIANT_CMD["C_native"]=""
VARIANT_CMD["CPP_native"]=""
VARIANT_CMD["C_wasm"]="$WASMTIME"
VARIANT_CMD["CPP_wasm"]="$WASMTIME"

# 用于并发运行时，存放每个任务的临时输出文件目录
TMP_DIR="tmp_results"
mkdir -p "$TMP_DIR"

# 函数：运行单个 benchmark 多次，计算平均时间（秒）
# 参数1：完整文件路径
# 参数2：variant（例如 C_native、C_wasm、CPP_native、CPP_wasm）
# 结果写入临时文件，文件名基于 benchmark名和 variant
run_benchmark() {
    local filepath="$1"
    local variant="$2"
    local suffix="${VARIANT_SUFFIX[$variant]}"
    
    # 提取 benchmark 名称：去掉 bin/ 前缀和后缀
    local rel_path="${filepath#bin/}"
    local bench_name="${rel_path%$suffix}"
    # 如果是 C 或 CPP，bench_name 可能还包含 .c 或 .cpp 后缀，这里去除
    bench_name="${bench_name%.c}"
    bench_name="${bench_name%.cpp}"
    
    local cmd_prefix=${VARIANT_CMD[$variant]}
    local total=0
    local count=0

    # 循环运行 NUM_RUNS 次，解析输出中的时间值（支持 ms 或 s）
    for (( i=1; i<=NUM_RUNS; i++ )); do
        if [ -n "$cmd_prefix" ]; then
            output=$("$cmd_prefix" "$filepath")
        else
            output=$("$filepath")
        fi

        # 使用 Bash 正则提取 "Time:" 后面的数字和单位
        if [[ "$output" =~ Time:\ ([0-9.]+)\ (ms|s) ]]; then
            value="${BASH_REMATCH[1]}"
            unit="${BASH_REMATCH[2]}"
            if [ "$unit" == "ms" ]; then
                # 转换为秒（使用 awk 做浮点运算）
                time_sec=$(awk "BEGIN {printf \"%.6f\", $value/1000}")
            else
                time_sec="$value"
            fi
            total=$(awk "BEGIN {printf \"%.6f\", $total + $time_sec}")
            ((count++))
        else
            echo "Warning: 无法解析时间输出。输出内容: $output"
        fi
    done

    if [ $count -gt 0 ]; then
        avg=$(awk "BEGIN {printf \"%.6f\", $total / $count}")
    else
        avg="0"
    fi

    # 写入 CSV（格式：Benchmark,Variant,AverageTime(s)）
    echo "${bench_name},${variant},${avg}" >> "$CSV_FILE"
    echo "Completed $bench_name ($variant): Average Time = ${avg} s"
}

# 并发运行所有 benchmark：对每个 variant，在 bin 目录下递归查找对应后缀文件
run_all() {
    for variant in "${!VARIANT_SUFFIX[@]}"; do
        suffix="${VARIANT_SUFFIX[$variant]}"
        # 查找匹配文件（递归搜索）
        files=$(find bin -type f -name "*${suffix}")
        for f in $files; do
            # 后台运行，每个任务写入自己的输出到 CSV
            run_benchmark "$f" "$variant" &
        done
    done
    wait
}

echo "Running benchmarks concurrently..."
run_all

echo "All benchmarks completed. Results saved in $CSV_FILE."
