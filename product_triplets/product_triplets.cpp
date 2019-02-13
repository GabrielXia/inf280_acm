#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <iterator>

using namespace std;
int main(int argc, char const *argv[]){
    int T, N;
    cin >> T;
    for(int i=0; i < T; i++) {
        cin >> N;
        unordered_map<unsigned long long,unsigned long long> m;
        set<unsigned long long> s;
        vector<unsigned long long> v(N);
        unsigned long long count = 0;
        for(int j=0; j<N; j++) {
            cin >> v[j];
            if (m.find(v[j]) != m.end()) {
                unsigned long long count_same = m.find(v[j])-> second + 1;
                m.erase(v[j]);
                m.insert({v[j], count_same});
            } else {
                m.insert(make_pair(v[j], 1));
                s.insert(v[j]);
            }
        }
        
        for(auto value1 = s.begin(); value1 != s.end(); value1 ++) {
            unsigned long long true_value1 = *(value1);
            if(true_value1 != 1 && true_value1 != 0) {
                unsigned long long more_count = m.find(true_value1) -> second;
                if (more_count > 1) {
                    unsigned long long value3 = true_value1 * true_value1;
                    if(m.find(value3) != m.end()) {
                        count += more_count * (more_count -1) / 2 * m.find(value3) -> second;
                    }
                }
                for(auto value2 = next(value1, 1); value2 != s.end(); value2++) {
                    unsigned long long value3 = (*value1) * (*value2);
                    if (m.find(value3) != m.end()) {
                        count += (m.find(*value1) -> second) * (m.find(*value2) -> second) * (m.find(value3) -> second);
                    }
                }
            }  else if (true_value1 == 0) {
                unsigned long long zero_count = m.find(0) -> second;
                if (zero_count > 2) {
                    count += zero_count * (zero_count - 1) * (zero_count -2) / 6;
                }
                if (zero_count >= 2) {
                    count += zero_count * (zero_count - 1) / 2 * (N - zero_count);
                }
            } else {
                unsigned long long one_count = m.find(1) -> second;
                if(one_count > 2) {
                    count += one_count * (one_count -1) * (one_count -2) / 6;
                }
                if (one_count >=1) {
                    for (auto value2 = next(value1, 1); value2 != s.end(); value2++) {
                        unsigned long long more_count = m.find(*value2) -> second;
                        count += one_count * (more_count * (more_count -1) / 2);
                    }
                }
            }
        }
        cout << "Case #" << i+1  << ": " <<  count << endl;
    }
    return 0;
}
