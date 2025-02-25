import csv
from collections import defaultdict
import matplotlib.pyplot as plt

# We'll sum times and count runs, then compute averages
native_times = defaultdict(list)
wasm_times = defaultdict(list)

# Read CSV
with open('results.csv', newline='') as f:
    reader = csv.DictReader(f)
    for row in reader:
        N = int(row['N'])
        native_times[N].append(float(row['NativeTime(s)']))
        wasm_times[N].append(float(row['Wasm3Time(s)']))

# Compute average per N
N_values = sorted(native_times.keys())
native_avgs = []
wasm_avgs = []

for N in N_values:
    native_avgs.append(sum(native_times[N]) / len(native_times[N]))
    wasm_avgs.append(sum(wasm_times[N]) / len(wasm_times[N]))

# Plot
plt.plot(N_values, native_avgs, marker='o', label='Native (avg)')
plt.plot(N_values, wasm_avgs, marker='o', label='Wasm3 (avg)')
plt.xlabel("Matrix Dimension N")
plt.ylabel("Execution Time (seconds)")
plt.title("Matrix Multiplication Performance: Native vs. Wasm3")
plt.legend()
plt.grid(True)
plt.savefig('matrix_mul_performance.png')
plt.show()
