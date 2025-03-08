import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

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

# Native results
df_native = pd.read_csv('benchmark_results.csv')
df_native['Environment'] = 'Native'
df_native['Benchmark'] = df_native['Benchmark'].apply(map_benchmark)

# Java WASM results
df_java_wasm = pd.read_csv('java_wasm_results.csv')
df_java_wasm['Environment'] = 'WASM'
df_java_wasm['Benchmark'] = df_java_wasm['Benchmark'].apply(map_benchmark)

# Python WASM results
df_python_wasm = pd.read_csv('python_wasm_results.csv')
df_python_wasm['Environment'] = 'WASM'
df_python_wasm['Language'] = 'Python'
df_python_wasm['Benchmark'] = df_python_wasm['Benchmark'].apply(map_benchmark)

# C WASM results
df_c_wasm = pd.read_csv('wasm_results_c.csv')
df_c_wasm['Environment'] = 'WASM'
df_c_wasm['Language'] = 'C'
df_c_wasm['Benchmark'] = df_c_wasm['Benchmark'].apply(map_benchmark)

# C++ WASM results
df_cpp_wasm = pd.read_csv('wasm_results_cpp.csv')
df_cpp_wasm['Environment'] = 'WASM'
df_cpp_wasm['Language'] = 'C++'
df_cpp_wasm['Benchmark'] = df_cpp_wasm['Benchmark'].apply(map_benchmark)

# Combine all data
df_all = pd.concat([df_native, df_java_wasm, df_python_wasm, df_c_wasm, df_cpp_wasm], ignore_index=True)
df_all['Input Size'] = pd.to_numeric(df_all['Input Size'], errors='coerce')

# Ensure a Language column exists
if 'Language' not in df_all.columns:
    df_all['Language'] = ''

# Create a label for each Language-Environment pair (e.g., "C_Native", "Java_WASM")
df_all['Label'] = df_all['Language'] + '_' + df_all['Environment']

# ----------------------------
# 2. Create pivot tables and draw table graphs for each benchmark
# ----------------------------

# The pivot table layout: rows = Label, columns = Input Size, values = Execution Time (ms)
# We aggregate using the mean in case of duplicate entries.
benchmarks = df_all['Benchmark'].unique()

# Create a directory to save the table graphs
output_dir = "benchmark_table_graphs"
os.makedirs(output_dir, exist_ok=True)

for bench in benchmarks:
    # Filter data for the current benchmark
    df_bench = df_all[df_all['Benchmark'] == bench]
    
    # Create the pivot table
    pivot = pd.pivot_table(df_bench, 
                           index='Label', 
                           columns='Input Size', 
                           values='Time (ms)', 
                           aggfunc='mean')
    
    # Optionally, sort the input sizes (columns) in ascending order
    pivot = pivot.reindex(sorted(pivot.columns), axis=1)
    
    # For Bubble Sort and Fibonacci, drop columns (input sizes) that are not present in every label
    if bench in ['Bubble Sort', 'Fibonacci']:
        pivot = pivot.dropna(axis=1, how='any')
    
    # If the pivot table becomes empty, skip this benchmark.
    if pivot.empty:
        print(f"Skipping benchmark {bench} because the pivot table is empty after dropping NaNs.")
        continue

    # Create a figure and add the table
    fig, ax = plt.subplots(figsize=(max(8, len(pivot.columns)*1.2), max(3, len(pivot.index)*0.5)))
    ax.axis('tight')
    ax.axis('off')
    
    # Create the table from the pivot data (round values to 2 decimals)
    the_table = ax.table(cellText=np.round(pivot.values, 2), 
                         rowLabels=pivot.index, 
                         colLabels=pivot.columns, 
                         loc='center',
                         cellLoc='center')
    
    # Format the table for better readability
    the_table.auto_set_font_size(False)
    the_table.set_fontsize(10)
    the_table.scale(1.2, 1.2)
    
    # Set a title for the table
    ax.set_title(f"Benchmark: {bench}", fontweight="bold", pad=20)
    
    # Save the figure
    output_filename = os.path.join(output_dir, f"table_{bench.replace(' ', '_')}.png")
    plt.savefig(output_filename, bbox_inches='tight')
    plt.close()
    
    print(f"Saved table graph for benchmark '{bench}' as {output_filename}")
