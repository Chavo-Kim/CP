//http://www.usaco.org/index.php?page=viewproblem2&cpid=567

#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v(7);
    for(int i = 0; i < 7; i++){
        cin >> v[i];
    }
    int three_sum = 0;
    for(int i = 0; i < 7; i++){
        three_sum += v[i];
    }
    three_sum /= 4;
    sort(v.begin(), v.end());
    cout << v[0] << " " << v[1] << " " << three_sum - v[0] - v[1];
    return 0;
}
