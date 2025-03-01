#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

int main() {
    const int MAXN = 10000000; 
    vector<bool> isPrime(MAXN, true);
    isPrime[0] = false;
    if(MAXN > 1) isPrime[1] = false;

    auto start = chrono::high_resolution_clock::now();

    for(int i = 2; i * i < MAXN; i++) {
        if(isPrime[i]) {
            for(int j = i * i; j < MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Sieve Time: " << duration << " ms" << endl;

    // count prime numbers
    // int count = 0;
    // for(int i = 2; i < MAXN; i++){
    //     if(isPrime[i]) count++;
    // }
    // cout << "Prime Count: " << count << endl;

    return 0;
}
