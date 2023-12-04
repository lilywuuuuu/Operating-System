#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

int n;
int t = 1;
int global_count = 0;

bool is_prime(int num) {
    if (num == 1) return false;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void count_primes(int t_index) {
    int count = 0;
    // distribute nums in a zig-zag way
    for (int i = t_index; i <= n; i += t * 2) {
        if (is_prime(i)) {
            count++;
        }
        if ((i + (t - t_index) * 2 + 1) <= n) {
            if (is_prime(i + (t - t_index) * 2 + 1)) {
                count++;
            }
        }
    }
    global_count += count;
}

int main(int argc, char* argv[]) {
    if (argc > 2 && string(argv[1]) == "-t") {
        t = stoi(argv[2]);
    }
    cin >> n;
    vector<thread> threads;
    for (int i = 1; i <= t; i++) {
        threads.emplace_back(thread(count_primes, i));
    }
    for (auto& t : threads)
        t.join();

    cout << global_count << endl;
    return 0;
}