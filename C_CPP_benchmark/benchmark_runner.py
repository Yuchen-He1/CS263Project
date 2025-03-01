#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import subprocess
import time
import os
import matplotlib.pyplot as plt

def run_benchmark(executable_path):
    """
    运行单个可执行文件并测量运行时间(秒)。
    返回(退出码, 耗时秒)。
    """
    start_time = time.time()
    # 使用 subprocess.run 来执行可执行文件
    # capture_output=True 可以在 Python 中捕获输出，但此处不一定需要
    result = subprocess.run([executable_path], capture_output=True)
    end_time = time.time()
    elapsed = end_time - start_time

    return result.returncode, elapsed

def main():
    # 这里列出所有可执行文件及其所在子目录
    # 对应上面 Makefile/子目录Makefile 生成的可执行文件名
    benchmarks = {
        "Bsort":               "Bsort/bsort",
        "coremark":            "coremark/coremark",
        "Fib_recursion":       "Fib_recursion/fib_recursion",
        "File_IO":             "File_IO/file_io",
        "Hanoi":               "Hanoi/hanoi",
        "matrix_multiplication": "matrix_multiplication/matrix_mul",
        "Qsort":               "Qsort/qsort",
        "Sieve":               "Sieve/sieve"
    }

    results = {}  # { benchmark_name: time_in_seconds }

    # 1) 先确保我们在顶层目录下执行 make (可选)
    print("Building all benchmarks (make all)...")
    build_ret = subprocess.run(["make", "all"])
    if build_ret.returncode != 0:
        print("Error: make failed.")
        return

    # 2) 逐个执行可执行文件并记录时间
    for name, path in benchmarks.items():
        # 判断可执行文件是否存在
        if not os.path.isfile(path):
            print(f"Warning: executable '{path}' not found. Skipped.")
            continue

        print(f"Running benchmark: {name} -> {path}")
        ret_code, elapsed_sec = run_benchmark(path)
        if ret_code == 0:
            results[name] = elapsed_sec
            print(f"  Done. Time: {elapsed_sec:.4f} s")
        else:
            print(f"  Error: return code = {ret_code}")

    # 3) 绘制柱状图
    if not results:
        print("No results to plot.")
        return

    # 根据 results 的键值对绘制
    bench_names = list(results.keys())
    times = [results[name] for name in bench_names]

    plt.figure(figsize=(10, 6))
    plt.bar(bench_names, times, color='skyblue')
    plt.xlabel("Benchmarks")
    plt.ylabel("Time (seconds)")
    plt.title("Benchmark Execution Time")
    plt.xticks(rotation=45)
    plt.tight_layout()

    # 4) 保存并显示图表
    plt.savefig("benchmark_results.png", dpi=150)
    print("Saved chart as benchmark_results.png")

    # 如需在脚本结束前显示图表，可解开以下注释
    # plt.show()

if __name__ == "__main__":
    main()
