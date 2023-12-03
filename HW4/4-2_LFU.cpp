#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(void){
    int blocks, k, n, miss = 0; 
    cin >> blocks >> k >> n;
    int sets = blocks/k; 
    vector<vector<int> > cache(sets); // cache -> sets -> blocks
    vector<vector<int> > freq(sets); // frequency of each data
    for (int index=0; index<n; index++){
        bool found = false; 
        int data; 
        cin >> data;
        for(int i=0; i<sets; i++){
            for (int j=0; j<cache[i].size(); j++){
                // data is found 
                if (data == cache[i][j]){ 
                    // cout << "[ O ] " << data << " found at (" << i << ", " << j << ")\n";
                    freq[i][j]++; 
                    found = true; 
                    break; 
                } 
            }
            if (found) break; 
        }
        if (!found){
            int s = index % sets; 
            // data is not found and set isn't full
            if (cache[s].size() < k){
                cache[s].push_back(data);
                freq[s].push_back(0);
            } 
            // data is not found and set is full
            else {
                int least_freq = INT_MAX;
                int freq_index = 0; 
                for (int j=0; j<k; j++){
                    if (freq[s][j] < least_freq){
                        least_freq = freq[s][j];
                        freq_index = j; 
                    }
                }
                cache[s][freq_index] = data;
                freq[s][freq_index] = 0;
            }
            // cout << "[ X ] " << data << " pushed at (" << s << ", " << cache[s].size()-1 << ")\n";
            miss++;
        }
    //     for(int i=0; i<sets; i++){
    //         cout << "cache " << i << ": ";
    //         for (int j=0; j<cache[i].size(); j++){
    //             cout << cache[i][j] << " ";
    //         } 
    //         cout << "\tfreq " << i << ": "; 
    //         for (int j=0; j<freq[i].size(); j++){
    //             cout << freq[i][j] << " ";
    //         } cout << endl; 
    //     } cout << endl; 
    }
    cout << "Total Cache Misses:" << miss << endl; 
    return 0;
}