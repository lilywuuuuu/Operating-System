#include <iostream>
#include <vector>
using namespace std;

int main(void){
    int blocks, n, miss = 0;
    cin >> blocks >> n;
    vector<int> cache(blocks, -1);
    for(int i=0; i<n; i++){
        int data;
        cin >> data;
        for(int j=0; j<blocks; j++){
            if (cache[j] == data) break; // data is in cache
            if (j == blocks-1){ // data is not in cache
                miss++;
                cache[i%blocks] = data;
                // cout << "miss: " << miss << "\tblock " << i%j << ": " << data << endl; 
            }
        }
    }
    cout << "Total Cache Misses:" << miss << endl; 

    return 0;
}