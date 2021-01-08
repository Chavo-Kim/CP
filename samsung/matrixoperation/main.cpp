//https://www.acmicpc.net/problem/17140

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n = 3, m = 3;
int map[101][101];
int x, y, k;

int sorted[101];

int radix[101];

bool comp(int l, int r){
    if(radix[l] == 0) return false;
    if(radix[r] == 0) return true;
    if(radix[l] != radix[r]) return radix[l] < radix[r];
    return l < r;
}

void init(){
    for(int i = 1; i <= 100; i++){
        radix[i] = 0;
    }
}

int sortArray(int num, bool dir){
    init();

    if(dir){
        for(int j = 0; j < m; j++){
            if(map[num][j] != 0){
                radix[map[num][j]]++;
            }
        }
    } else {
        for(int i = 0 ; i < n; i++){
            if(map[i][num] != 0){
                radix[map[i][num]]++;
            }
        }
    }

    sort(sorted, sorted+100, comp);

    int cnt = 0;

    if(dir){
        while(radix[sorted[cnt/2]] != 0 && cnt < 100){
            map[num][cnt] = sorted[cnt/2];
            map[num][cnt+1] = radix[sorted[cnt/2]];
            cnt += 2;
        }
    } else {
        while(radix[sorted[cnt/2]] != 0 && cnt < 100){
            map[cnt][num] = sorted[cnt/2];
            map[cnt+1][num] = radix[sorted[cnt/2]];
            cnt += 2;
        }
    }

    return cnt;
}

void simul(){
    int max_val = 0;
    if(n >= m){
        for(int i = 0; i < n; i++){
            int tmp_val = sortArray(i, true);
            if(tmp_val < m){
                for(int j = tmp_val; j < m; j++){
                    map[i][j] = 0;
                }
            }
            if(max_val < tmp_val)
                max_val = tmp_val;
        }
        m = max_val;
    } else {
        for(int j = 0; j < m; j++){
            int tmp_val = sortArray(j, false);
            if(tmp_val < n){
                for(int i = tmp_val; i < n; i++){
                    map[i][j] = 0;
                }
            }
            if(max_val < tmp_val)
                max_val = tmp_val;
        }
        n = max_val;
    }
}

int main() {
    freopen("../input.txt", "r", stdin);

    scanf("%d %d %d", &x, &y, &k);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &map[i][j]);
        }
    }

    for(int i = 0; i < 100; i++){
        sorted[i] = i + 1;
    }
    int ans = 0;
    while(map[x-1][y-1] != k && ans < 101){
        ans++;
        simul();
    }
    printf("%d", (ans == 101)?-1:ans);
    return 0;
}
