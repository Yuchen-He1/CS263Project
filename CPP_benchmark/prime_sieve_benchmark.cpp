#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

void prime_sieve(int N, vector<bool>& prime) {
    fill(prime.begin(), prime.end(), true);
    prime[0] = prime[1] = false;
    for (int p = 2; p * p <= N; p++)
        if (prime[p])
            for (int i = p * p; i <= N; i += p)
                prime[i] = false;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <upper_limit>" << endl;
        return 1;
    }

    int N = stoi(argv[1]);
    vector<bool> prime(N + 1);

    auto start = high_resolution_clock::now();
    prime_sieve(N, prime);
    auto end = high_resolution_clock::now();

    cout << "Prime Sieve | Upper Limit: " << N 
         << " | Time: " << duration<double, milli>(end - start).count() << " ms" << endl;
    return 0;
}
