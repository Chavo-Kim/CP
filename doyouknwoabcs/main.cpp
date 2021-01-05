//http://www.usaco.org/index.php?page=viewproblem2&cpid=1059

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    vector<ll> v(7);
    for(int i = 0; i < 7; i++){
        cin >> v[i];
    }
    ll three_sum = 0;
    for(int i = 0; i < 7; i++){
        three_sum += v[i];
    }
    three_sum /= 4;
    sort(v.begin(), v.end());
    cout << v[0] << " " << v[1] << " " << three_sum - v[0] - v[1];
    return 0;
}
