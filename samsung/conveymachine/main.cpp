#include <cstdio>

using namespace std;

int n, k;
int arr[201];
int rob[200001];
int trans[201];
int rob_cnt = 0;
int rob_start = 0;
int ans = 1;

void debug(){
    printf("arr :");
    for(int i = 0 ; i < 2* n ; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("trans :");
    for(int i = 0 ; i < 2* n ; i++){
        printf("%d ", trans[i]);
    }
    printf("\n");
    printf("rob :");
    for(int i = rob_start ; i < rob_cnt ; i++){
        printf("%d ", rob[i]);
    }
    printf("\n");

}

void checkDown(){
    for(int i = rob_start; i < rob_cnt; i++){
        if(rob[i] == n-1)
            rob_start++;
    }
}

void round_convey(){
    int tmp = trans[2*n-1];
    for(int i = n*2 - 2; i >= 0; i--){
        trans[i+1] = trans[i];
    }
    trans[0] = tmp;
    for(int i = rob_start; i < rob_cnt; i++){
        rob[i]++;
    }
    checkDown();
}

bool canMove(int idx){
    if(arr[trans[rob[idx]+1]] <= 0)
        return false;
    if(idx == rob_start)
        return true;
    return rob[idx-1] != rob[idx] + 1;
}

void moveRob(){
    for(int i = rob_start; i < rob_cnt; i++){
        if(canMove(i)) {
            rob[i]++;
            arr[trans[rob[i]]]--;
        }
    }
    checkDown();
}

void addRob(){
    if(arr[trans[0]] > 0){
        rob[rob_cnt++] = 0;
        arr[trans[0]]--;
    }
}

bool checkFinish(){
    int cnt = 0;
    for(int i = 0 ; i < 2*n; i++){
        if(arr[i] == 0)
            cnt++;
    }
    return cnt < k;
}

bool simul(){
    round_convey();
    moveRob();
    addRob();
    return checkFinish();
}

int main() {
    freopen("../input.txt", "r", stdin);

    scanf("%d %d", &n, &k);

    for(int i = 0; i < n*2; i++){
        scanf("%d ", &arr[i]);
        trans[i] = i;
    }


    while(simul()){
        ans++;
        //debug();
    }

    printf("%d", ans);

    return 0;
}
