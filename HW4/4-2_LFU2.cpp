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
                    int f = freq[i][j]; 
                    // move data to the back (most recently used)
                    cout << "[ O ] " << data << " found at (" << i << ", " << j << ")\n";
                    for(int l=j; l<cache[i].size()-1; l++){ 
                        cache[i][l] = cache[i][l+1];
                        freq[i][l] = freq[i][l+1];
                    }
                    cache[i][cache[i].size()-1] = data;
                    freq[i][cache[i].size()-1] = f+1; 
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
                for (int j=k-1; j>=0; j--){
                    if (freq[s][j] < least_freq){
                        least_freq = freq[s][j];
                        freq_index = j; 
                    }
                }
                for (int j=freq_index; j<k-1; j++){
                    cache[s][j] = cache[s][j+1];
                    freq[s][j] = freq[s][j+1];
                } 
                cache[s][k-1] = data;
                freq[s][k-1] = 0;
            }
            cout << "[ X ] " << data << " pushed at (" << s << ", " << cache[s].size()-1 << ")\n";
            miss++;
        }
        for(int i=0; i<sets; i++){
            cout << "cache " << i << ": ";
            for (int j=0; j<cache[i].size(); j++){
                cout << cache[i][j] << " ";
            } 
            cout << "\tfreq " << i << ": "; 
            for (int j=0; j<freq[i].size(); j++){
                cout << freq[i][j] << " ";
            } cout << endl; 
        } cout << endl; 
    }
    cout << "Total Cache Misses: " << miss << endl; 
    return 0;
}