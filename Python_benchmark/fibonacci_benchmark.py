import time

def fibonacci(n):
    if n <= 1:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)

def main():
    N = int(input("Enter Fibonacci number index: "))

    start_time = time.perf_counter()
    result = fibonacci(N)
    end_time = time.perf_counter()

    print(f"Fibonacci | N: {N} | Result: {result} | Time: {(end_time - start_time) * 1000:.2f} ms")

if __name__ == "__main__":
    main()
