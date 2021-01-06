#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll t;
ll n;
ll x;
ll arr[100001];
ll sum;

//ll init(int node, int start, int end){
//    if(start==end)
//        return tree[node] = arr[start];
//
//    int mid = (start+end) / 2;
//
//    return tree[node] = init(node*2, start, mid) + init(node * 2 + 1, mid + 1, end);
//}

int main() {
    freopen("../input.txt", "r", stdin);

    cin >> t;

    for(int test = 0; test < t; test++){
        cin >> n;
        cin >> x;
        ll sec = 0;
        sum = 0;
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            sum += arr[i];
            sec += (ll)ceil((double)arr[i]/x);
        }
        cout << (ll)ceil((double)sum / x) << " ";
        cout << sec << endl;
    }


    return 0;
}