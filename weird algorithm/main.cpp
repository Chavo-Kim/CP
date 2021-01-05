//https://cses.fi/problemset/task/1068

#include <iostream>

typedef long long ll;

using namespace std;

ll processPrint(ll k){
    if((k & 1) == 1){
        printf("%lld ", 3*k + 1);
        return 3 * k + 1;
    } else {
        printf("%lld ", k / 2);
        return k / 2;
    }
}

int main() {
    ll n;
    cin >> n;
    printf("%lld ", n);
    ll k = n;
    while(k != 1){
        k = processPrint(k);
    }
    return 0;
}
