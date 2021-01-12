//
// Created by Chavo Kim on 2021/01/08.
//

#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int arr[300001];


int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> t;
    for(int test = 0; test < t; test++){
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
    }
    return 0;
}
