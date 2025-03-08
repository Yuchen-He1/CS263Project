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
    df_native, df_java_wasm, df_python_wasm, df_c_wasm, df_cpp_wasm
], ignore_index=True)
df_all['Input Size'] = pd.to_numeric(df_all['Input Size'], errors='coerce')

# ----------------------------
# 2. Select representative record per group (always choose the row with maximum Input Size)
# ----------------------------
def select_representative_max(group):
    return group.loc[group['Input Size'].idxmax()]

df_best = df_all.groupby(['Language', 'Benchmark', 'Environment']).apply(select_representative_max).reset_index(drop=True)

# Create a new label for each Language-Environment pair (e.g., "C_Native", "Java_WASM", etc.)
df_best['Label'] = df_best['Language'] + '_' + df_best['Environment']

# Define benchmark order for plotting consistency
benchmark_order = [
    'Bubble Sort',
    'Fibonacci',
    'Tower of Hanoi',
    'Matrix Multiplication',
    'QuickSort',
    'Prime Number Sieve'
]

# ----------------------------
# 3. Generate pivot table and apply log10 transformation
# ----------------------------
pivot_df = df_best.pivot(index='Benchmark', columns='Label', values='Time (ms)')
pivot_df = pivot_df.reindex(benchmark_order)

# Apply log10 to execution time (only valid for positive values)
pivot_df = pivot_df.applymap(lambda x: np.log10(x) if pd.notnull(x) and x > 0 else np.nan)

# ----------------------------
# 4. Plot grouped bar chart with annotations for selected Input Size
# ----------------------------
labels = pivot_df.index.tolist()    # x-axis: benchmarks
n_groups = len(labels)
n_bars = pivot_df.shape[1]           # Number of Language_Environment groups per benchmark
x = np.arange(n_groups)
width = 0.8 / n_bars                 # Total group width set to 0.8

fig, ax = plt.subplots(figsize=(12, 6))
for i, col in enumerate(pivot_df.columns):
    ax.bar(x + i * width, pivot_df[col].values, width, label=col)

ax.set_xlabel('Benchmark')
ax.set_ylabel('log10(Execution Time (ms))')
ax.set_title('Native vs WASM Execution Time Comparison (Max Input Size)')
ax.set_xticks(x + (n_bars - 1) * width / 2)
ax.set_xticklabels(labels, rotation=15, ha='right')
ax.legend()

# Annotate each benchmark with its selected Input Size
for i, benchmark in enumerate(labels):
    # Assume that for the same benchmark, the selected input size is consistent across languages.
    selected_size = df_best[df_best['Benchmark'] == benchmark]['Input Size'].iloc[0]
    y_vals = pivot_df.loc[benchmark].dropna().values
    max_y = max(y_vals) if len(y_vals) > 0 else 0
    ax.text(x[i] + (n_bars - 1) * width / 2, max_y * 1.05,
            f"Input Size: {selected_size}",
            ha='center', va='bottom', fontsize=10, color='black')

plt.tight_layout()
plt.savefig('native_vs_wasm_comparison_log.png')
plt.close()
