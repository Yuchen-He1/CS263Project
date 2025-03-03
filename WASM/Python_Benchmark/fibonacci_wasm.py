def fibonacci(n):
    if n <= 1:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)

def run_fibonacci(N):
    return fibonacci(N)  # Simply returns Fibonacci result
