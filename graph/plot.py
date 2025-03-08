import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def map_benchmark(bench):
    """
    Normalize different benchmark names to a common set of names.
    """
    bench_lower = bench.lower()
    if 'bubble' in bench_lower:
        return 'Bubble Sort'
    elif 'fibonacci' in bench_lower:
        return 'Fibonacci'
    elif 'hanoi' in bench_lower:
        return 'Tower of Hanoi'
    elif 'matrix' in bench_lower:
        return 'Matrix Multiplication'
    elif 'quick' in bench_lower or 'qsort' in bench_lower:
        return 'QuickSort'
    elif 'prime' in bench_lower:
        return 'Prime Number Sieve'
    else:
        return bench

# ----------------------------
# 1. Read CSV files and process data
# ----------------------------

# Native results for all languages
df_native = pd.read_csv('benchmark_results.csv')
df_native['Environment'] = 'Native'
df_native['Benchmark'] = df_native['Benchmark'].apply(map_benchmark)

# Java WASM
df_java_wasm = pd.read_csv('java_wasm_results.csv')
df_java_wasm['Environment'] = 'WASM'
df_java_wasm['Benchmark'] = df_java_wasm['Benchmark'].apply(map_benchmark)

# Python WASM
df_python_wasm = pd.read_csv('python_wasm_results.csv')
df_python_wasm['Environment'] = 'WASM'
df_python_wasm['Language'] = 'Python'
df_python_wasm['Benchmark'] = df_python_wasm['Benchmark'].apply(map_benchmark)

# C WASM
df_c_wasm = pd.read_csv('wasm_results_c.csv')
df_c_wasm['Environment'] = 'WASM'
df_c_wasm['Language'] = 'C'
df_c_wasm['Benchmark'] = df_c_wasm['Benchmark'].apply(map_benchmark)

# C++ WASM
df_cpp_wasm = pd.read_csv('wasm_results_cpp.csv')
df_cpp_wasm['Environment'] = 'WASM'
df_cpp_wasm['Language'] = 'C++'
df_cpp_wasm['Benchmark'] = df_cpp_wasm['Benchmark'].apply(map_benchmark)

# Combine all data
df_all = pd.concat([
    df_native,
    df_java_wasm,
    df_python_wasm,
    df_c_wasm,
    df_cpp_wasm
], ignore_index=True)
df_all['Input Size'] = pd.to_numeric(df_all['Input Size'], errors='coerce')

# ----------------------------
# 2. Select representative record per group
# ----------------------------
def select_representative(group):
    """
    For each (Language, Benchmark, Environment) group, select a representative row.
    For "Bubble Sort", choose the row with the smallest input size,
    for other benchmarks choose the row with the largest input size.
    """
    if group['Benchmark'].iloc[0] == 'Bubble Sort':
        return group.loc[group['Input Size'].idxmin()]
    else:
        return group.loc[group['Input Size'].idxmax()]

df_best = df_all.groupby(['Language', 'Benchmark', 'Environment']).apply(select_representative).reset_index(drop=True)

# Create a new label for each language/environment pair
df_best['Label'] = df_best['Language'] + '_' + df_best['Environment']

# Define benchmark order (optional)
benchmark_order = [
    'Bubble Sort',
    'Fibonacci',
    'Tower of Hanoi',
    'Matrix Multiplication',
    'QuickSort',
    'Prime Number Sieve'
]

# ----------------------------
# 3. Plot graphs
# ----------------------------

# (A) Main graph for languages other than Python
df_best_main = df_best[df_best['Language'] != 'Python']
pivot_main = df_best_main.pivot(index='Benchmark', columns='Label', values='Time (ms)')
existing_benchmarks = [b for b in benchmark_order if b in pivot_main.index]
pivot_main = pivot_main.reindex(existing_benchmarks)

labels = pivot_main.index.tolist()
n_groups = len(labels)
n_bars = pivot_main.shape[1]
x = np.arange(n_groups)
width = 0.8 / n_bars

fig, ax = plt.subplots(figsize=(12, 6))
for i, col in enumerate(pivot_main.columns):
    ax.bar(x + i * width, pivot_main[col].values, width, label=col)

ax.set_xlabel('Benchmark')
ax.set_ylabel('Execution Time (ms)')
ax.set_title('Native vs WASM Execution Time Comparison (Excluding Python)')
ax.set_xticks(x + (n_bars - 1) * width / 2)
ax.set_xticklabels(labels, rotation=15, ha='right')
ax.legend()
# Annotate each benchmark with its selected input size
for i, benchmark in enumerate(labels):
    # 从 df_best_main 中取一个值（所有语言应该是一致的）
    selected_size = df_best_main[df_best_main['Benchmark'] == benchmark]['Input Size'].iloc[0]
    y_vals = pivot_main.loc[benchmark].dropna().values
    max_y = max(y_vals) if len(y_vals) > 0 else 0
    ax.text(x[i] + (n_bars - 1) * width / 2, max_y * 1.05,
            f"Input Size: {selected_size}",
            ha='center', va='bottom', fontsize=10, color='black')

plt.tight_layout()
plt.savefig('native_vs_wasm_excluding_python.png')
plt.close()

# (B) Python-only graph
df_best_python = df_best[df_best['Language'] == 'Python']
pivot_python = df_best_python.pivot(index='Benchmark', columns='Label', values='Time (ms)')
existing_benchmarks = [b for b in benchmark_order if b in pivot_python.index]
pivot_python = pivot_python.reindex(existing_benchmarks)

labels = pivot_python.index.tolist()
n_groups = len(labels)
n_bars = pivot_python.shape[1]
x = np.arange(n_groups)
width = 0.8 / n_bars

fig, ax = plt.subplots(figsize=(12, 6))
for i, col in enumerate(pivot_python.columns):
    ax.bar(x + i * width, pivot_python[col].values, width, label=col)

ax.set_xlabel('Benchmark')
ax.set_ylabel('Execution Time (ms)')
ax.set_title('Python: Native vs WASM Execution Time Comparison')
ax.set_xticks(x + (n_bars - 1) * width / 2)
ax.set_xticklabels(labels, rotation=15, ha='right')
ax.legend()
# Annotate each benchmark with its selected input size
for i, benchmark in enumerate(labels):
    selected_size = df_best_python[df_best_python['Benchmark'] == benchmark]['Input Size'].iloc[0]
    y_vals = pivot_python.loc[benchmark].dropna().values
    max_y = max(y_vals) if len(y_vals) > 0 else 0
    ax.text(x[i] + (n_bars - 1) * width / 2, max_y * 1.05,
            f"Input Size: {selected_size}",
            ha='center', va='bottom', fontsize=10, color='black')

plt.tight_layout()
plt.savefig('python_native_vs_wasm_comparison.png')
plt.close()
