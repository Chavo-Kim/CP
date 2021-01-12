//https://www.acmicpc.net/problem/20061

#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int ans;
int tmp[6][4];
int green[6][4];
int blue[6][4];

bool InRange(int x, int y){
    return x >= 0 && x < 6 && y >= 0 && y < 4;
}

void init(){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            tmp[i][j] = 0;
        }
    }

}

void debug(){
    printf("green:\n");
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            printf("%d ", green[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("blue:\n");
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            printf("%d ", blue[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int gravity(int x, int y, bool isGreen){
    if(isGreen){
        int curr = 0;
        while(true) {
            if (!InRange(curr, y) || green[curr][y] != 0)
                return curr - 1;
            curr++;
        }
    } else {
        int curr = 0;
        while(true) {
            if (!InRange(curr, x) || blue[curr][x] != 0)
                return curr - 1;
            curr++;
        }
    }
}

void moveArray(int start, int k, bool isGreen){
    if(k == 0){
        return;
    }
    init();
    if(isGreen) {
        for (int i = start-1; i >= 0; i--) {
            for (int j = 0; j < 4; j++) {
                tmp[i+1][j] = green[i][j];
            }
        }

        for(int i = 1; i < start+1; i++){
            for(int j = 0; j < 4; j++){
                green[i][j] = tmp[i][j];
            }
        }
    } else {
        for (int i = start-1; i >= 0; i--) {
            for (int j = 0; j < 4; j++) {
                tmp[i+1][j] = blue[i][j];
            }
        }

        for(int i = 1; i < start+1; i++){
            for(int j = 0; j < 4; j++){
                blue[i][j] = tmp[i][j];
            }
        }
    }
}

void moveArray(int k, bool isGreen){
    if(k == 0){
        return;
    }
    init();
    if(isGreen) {
        for (int i = 5; i >= k; i--) {
            for (int j = 0; j < 4; j++) {
                tmp[i][j] = green[i-k][j];
            }
        }

        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 4; j++){
                green[i][j] = tmp[i][j];
            }
        }
    } else {
        for (int i = 5; i >= k; i--) {
            for (int j = 0; j < 4; j++) {
                tmp[i][j] = blue[i-k][j];
            }
        }

        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 4; j++){
                blue[i][j] = tmp[i][j];
            }
        }
    }
}

int remove_line(bool isGreen){
    int ret = 0;
    if(isGreen){
        for(int i = 5; i >= 2; i--){
            bool isFull = true;
            for(int j = 0; j < 4; j++){
                if(green[i][j] == 0){
                    isFull = false;
                    break;
                }
            }
            if(isFull){
                ret++;
                moveArray(i, 1, true);
                i++;
            }
        }
        int k = 0;
        for(int i = 0; i <= 1; i++){
            bool isExist = false;
            for(int j = 0; j < 4; j++){
                if(green[i][j] != 0){
                    isExist = true;
                    break;
                }
            }
            if(isExist) k++;
        }
        moveArray(k, true);
        return ret;
    }

    else{
        for(int i = 5; i >= 2; i--){
            bool isFull = true;
            for(int j = 0; j < 4; j++){
                if(blue[i][j] == 0){
                    isFull = false;
                    break;
                }
            }
            if(isFull){
                ret++;
                moveArray(i, 1, false);
                i++;
            }
        }
        int k = 0;
        for(int i = 0; i <= 1; i++){
            bool isExist = false;
            for(int j = 0; j < 4; j++){
                if(blue[i][j] != 0){
                    isExist = true;
                    break;
                }
            }
            if(isExist) k++;
        }
        moveArray(k, false);
        return ret;
    }
}

int query_green(int t, int x, int y){
    if(t == 1){
        green[gravity(x, y, true)][y] = 1;
    } else if(t==2) {
        int pos = min(gravity(x, y, true), gravity(x, y+1, true));
        green[pos][y] = green[pos][y+1] = 1;
    } else {
        int pos = gravity(x, y, true);
        green[pos][y] = 1;
        green[pos - 1][y] = 1;
    }
    return remove_line(true);
}

int query_blue(int t, int x, int y){
    if(t == 1){
        blue[gravity(x, y, false)][x] = 1;
    } else if(t==2) {
        int pos = gravity(x, y, false);
        blue[pos][x] = 1;
        blue[pos - 1][x] = 1;
    } else {
        int pos = min(gravity(x, y, false), gravity(x + 1, y, false));
        blue[pos][x] = blue[pos][x+1] = 1;
    }
    return remove_line(false);
}

int query(int t, int x, int y){
    int ret = 0;
    ret += query_blue(t, x, y);
    ret += query_green(t, x, y);
    return ret;
}

int count(){
    int cnt = 0;
    for(int i = 2; i < 6; i++){
        for(int j = 0 ; j < 4; j++){
            if(green[i][j] != 0) cnt++;
        }
    }

    for(int i = 2; i < 6; i++){
        for(int j = 0 ; j < 4; j++){
            if(blue[i][j] != 0) cnt++;
        }
    }

    return cnt;
}

int main() {
    freopen("../input.txt", "r", stdin);

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        int t, x, y;
        scanf("%d %d %d", &t, &x, &y);
        ans += query(t, x, y);
        debug();
    }

    printf("%d\n%d", ans, count());
    return 0;
}
