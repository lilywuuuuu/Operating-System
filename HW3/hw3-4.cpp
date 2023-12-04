#include <atomic>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

int n, m;
vector<uint64_t> subsets;
uint64_t one = static_cast<uint64_t>(1), global_count = 0;
vector<thread> threads;
vector<int> local_count;

void solve(int index, uint64_t current, int thread_index) {
    if (index == m) {
        if (current == (one << n) - 1) local_count[thread_index]++;
    } else {
        solve(index + 1, current, thread_index);
        solve(index + 1, current | subsets[index], thread_index);
    }
}

int main(int argc, char* argv[]) {
    cin >> n >> m;
    subsets.resize(m);
    for (int i = 0; i < m; i++) {
        int p, temp;
        cin >> p;
        for (int j = 0; j < p; j++) {
            cin >> temp;
            subsets[i] |= (one << temp);
        }
    }

    int t = 1;  // thread count
    if (argc > 2 && string(argv[1]) == "-t") {
        t = stoi(argv[2]);
    }
    local_count.resize(t, 0);

    if (t == 1) {  // 1 thread
        solve(0, 0, 0);
    } else if (t == 2 || m == 1) {  // 2 threads or only 1 subset
        threads.emplace_back(thread(solve, 1, 0, 0));
        threads.emplace_back(thread(solve, 1, subsets[0], 1));
    } else if (t == 4 || m == 2) {  // 4 threads or only 2 subsets
        threads.emplace_back(thread(solve, 2, 0, 0));
        threads.emplace_back(thread(solve, 2, subsets[0], 1));
        threads.emplace_back(thread(solve, 2, subsets[1], 2));
        threads.emplace_back(thread(solve, 2, subsets[0] | subsets[1], 3));
    } else {  // 8 threads and at least 3 sets
        threads.emplace_back(thread(solve, 3, 0, 0));
        threads.emplace_back(thread(solve, 3, subsets[0], 1));
        threads.emplace_back(thread(solve, 3, subsets[1], 2));
        threads.emplace_back(thread(solve, 3, subsets[2], 3));
        threads.emplace_back(thread(solve, 3, subsets[0] | subsets[1], 4));
        threads.emplace_back(thread(solve, 3, subsets[0] | subsets[2], 5));
        threads.emplace_back(thread(solve, 3, subsets[1] | subsets[2], 6));
        threads.emplace_back(thread(solve, 3, subsets[0] | subsets[1] | subsets[2], 7));
    }
    for (auto& t : threads) {
        t.join();
    }
    for (int i = 0; i < t; i++) {
        global_count += local_count[i];
    }
    cout << global_count << endl;
    return 0;
}
