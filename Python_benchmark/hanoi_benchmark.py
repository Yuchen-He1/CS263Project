import time

def hanoi(n, from_rod, aux_rod, to_rod):
    if n == 1:
        return
    hanoi(n - 1, from_rod, to_rod, aux_rod)
    hanoi(n - 1, aux_rod, from_rod, to_rod)

def main():
    N = int(input("Enter number of disks: "))

    start_time = time.perf_counter()
    hanoi(N, 'A', 'B', 'C')
    end_time = time.perf_counter()

    print(f"Hanoi | Disks: {N} | Time: {(end_time - start_time) * 1000:.2f} ms")

if __name__ == "__main__":
    main()
