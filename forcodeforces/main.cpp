//
// Created by Chavo Kim on 2021/01/08.
//

#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int arr[300001];

bool isValley(int j){
    return ((arr[j-1] < arr[j]) && (arr[j] > arr[j+1])) || ((arr[j-1] > arr[j]) && (arr[j] < arr[j+1]));
}


int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);

    cin >> t;

    for(int test = 0; test < t; test++){
        cin >> n;

        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }

        int sum = 0;
        int max_con = 0;
        int tmp_max = 0;
        bool isCon = false;

        for(int i = 1; i < n-1; i++){
            if(isValley(i)) {
                sum++;
                tmp_max++;
                isCon = true;
            } else {
                if(isCon){
                    if(max_con < tmp_max)
                        max_con = tmp_max;
                    tmp_max = 0;
                    isCon = false;
                }
            }
        }

        if(isCon){
            if(max_con < tmp_max)
                max_con = tmp_max;
        }

        if(max_con >= 3){
            sum -= 3;
        } else if(max_con == 2){
            sum -= 2;
        } else if(max_con == 1){
            sum-=1;
        }

        cout << sum << "\n";
    }
    return 0;
}
