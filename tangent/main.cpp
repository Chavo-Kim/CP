//https://www.acmicpc.net/problem/14890

#include <cstdio>
#include <cmath>

using namespace std;

int n,l;
int map[101][101];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

bool InRange(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool isOkay(int i, int j, int dir){
    int x = i, y = j;
    int cnt = 1;
    int idx = 0;

    while(true) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if(!InRange(nx, ny)) {
            if(idx == 1) {
                if(cnt < l)
                    return false;
            }
            cnt = 1;
            break;
        }
        if(map[x][y] == map[nx][ny]) {
            cnt++;
        }
        else if(map[x][y] - map[nx][ny] == 1){
            if(idx == 1){
                if(cnt < l)
                    return false;
            }
            cnt = 1;
            idx = map[x][y] - map[nx][ny];
        } else if(map[x][y] - map[nx][ny] == -1){
            if(idx == 1){
                if(cnt < l)
                    return false;
                else
                    cnt -= l;

                if(cnt < l)
                    return false;
                else
                    cnt = 1;
            }

            idx = map[x][y] - map[nx][ny];

        } else {
            return false;
        }
        x = nx; y = ny;
    }
//    if(cnt == 1){
//        printf("%d %d\n", i, j);
//    }
    return cnt == 1 ;
}

int simul(){
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(isOkay(i, 0, 0) && isOkay(i, n-1, 1)) ans++;
    }
    for(int j = 0; j < n; j++){
        if(isOkay(0, j, 2) && isOkay(n-1, j, 3)) ans++;
    }
    return ans;
}

int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d %d", &n, &l);
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n; j++){
            scanf("%d ",&map[i][j]);
        }
    }
    printf("%d", simul());
    return 0;
}
