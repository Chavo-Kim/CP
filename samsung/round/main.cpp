#include <iostream>

int round_map[51][51];
bool removed[51][51];
int n, m, t;

void round_simul(int num, int d, int k){
    if(d == 1){
        k = (m - k);
    }
    int tmp[51];
    for(int i = 0; i < m; i++){
        tmp[(i+k)%m] = round_map[num][i];
    }
    for(int i = 0; i < m; i++){
        round_map[num][i] = tmp[i];
    }
}

void findNear(int i, int j){
    int tmp = round_map[i][j];
    if(i < n-1) {
        if (tmp == round_map[i + 1][j]) {
            removed[i][j] = removed[i + 1][j] = true;
        }
    }
    if ( i > 0){
        if(tmp == round_map[i-1][j]){
            removed[i][j] = removed[i-1][j] = true;
        }
    }
    if(tmp == round_map[i][(j+1)%m]){
        removed[i][j] = removed[i][(j+1)%m] = true;
    }
    if(tmp == round_map[i][(j-1+m)%m]){
        removed[i][j] = removed[i][(j-1+m)%m] = true;
    }

}

void renew(int num){

    for(int i = 0; i < m; i++){
        if(round_map[num][i] != 0)
            findNear(num, i);
    }
}

int makeZero(){
    bool isRemove = false;
    int ret = 0;
    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(removed[i][j]) {
                round_map[i][j] = 0;
                isRemove = true;
            }
            else if(round_map[i][j] != 0) {
                ret += round_map[i][j];
                cnt++;
            }
        }
    }
    return (isRemove)?0:((cnt != 0)?(ret/cnt):(cnt));
}

void init(){

    for(int i = 0; i < n ;i ++){
        for(int j = 0 ; j < m; j++){
            removed[i][j] = false;
        }
    }

}

void roundSum(int sum){
    for(int i = 0; i < n ;i ++){
        for(int j = 0 ; j < m; j++){
            if(round_map[i][j] != 0){
                if(round_map[i][j] > sum)
                    round_map[i][j]--;
                else if(round_map[i][j] < sum)
                    round_map[i][j]++;
            }
        }
    }
}

void query(int x, int d, int k){
    for(int i = x-1; i < n; i += x){
        round_simul(i, d, k);
    }
    for(int i = 0; i < n; i++){
        renew(i);
    }
    int sum = makeZero();
    init();
    if(sum != 0) {
        roundSum(sum);
    }
}

int ans(){
    int ret = 0;
    for(int i = 0; i < n ;i ++){
        for(int j = 0 ; j < m; j++){
            ret += round_map[i][j];
        }
    }
    return ret;
}

int main() {
    //freopen("../input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &t);
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d ", &round_map[i][j]);
        }
    }
    for(int i = 0; i < t; i++){
        int x, d, k;
        scanf("%d %d %d", &x, &d, &k);
        query(x, d, k);
    }
    printf("%d", ans());
    return 0;
}
