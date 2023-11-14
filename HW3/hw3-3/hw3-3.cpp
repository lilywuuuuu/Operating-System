#include <iostream>
#include <thread>
#include <vector>

using namespace std;

int n, global_count = 0;
mutex mtx;

bool is_prime(int num) {
    if (num == 1) return false;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void count_primes(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            count++;
        }
    }
    {
        lock_guard<mutex> lock(mtx);
        global_count+=count;
    }
}
 
int main(int argc, char* argv[]) {
    int t = 1;
    if (argc > 2 && string(argv[1]) == "-t") // check if there's argument -t 
        t = stoi(argv[2]); // use t threads

    cin >> n;
    vector<thread> threads;
    int num_per_t = n/t; // num per thread
    for (int i = 0; i < t; i++) {
        int start = i * num_per_t + 1;
        int end = (i == t - 1) ? n : start + num_per_t - 1;
        threads.emplace_back(thread(count_primes, start, end));
        // cout << start << " " << end << endl;
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << global_count << endl;
    return 0;
}
