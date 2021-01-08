//https://www.acmicpc.net/problem/15684

#include <cstdio>
#include <vector>

using namespace std;

int n, m, h;
int* nums[11];
int dp[31][11];
bool swapable[31][11];
bool isPossible;

struct line{
    int a;
    int b;
    line(int a, int b):a(a), b(b){

    }
};

vector<line*> lines;

int getRoot(int num){
    int curr_h = h;
    int curr_num = num;
    while(curr_h >= 0){
        curr_num = dp[curr_h--][curr_num];
    }
    return curr_num;
}


void line_swap(int a, int b){
    int tmp = (dp[a+1][b]);
    (dp[a+1][b]) = (dp[a+1][b+1]);
    (dp[a+1][b+1]) = tmp;
}

bool isRight(){
    for(int i = 0; i < n; i++){
        if(getRoot(i) != i)
            return false;
    }
    return true;
}

int addSwapable(int a, int b){
    int ret = 0;
    swapable[a][b] = true;
    if(b < n-2){
        if(swapable[a][b+1] == false) {
            swapable[a][b + 1] = true;
            ret += 2;
        }
    }
    if(b > 0){
        if(swapable[a][b-1] == false) {
            swapable[a][b - 1] = true;
            ret += 1;
        }
    }
    return ret;
}

void subSwapable(int tmp, int a, int b){
    swapable[a][b] = false;
    if(b < n-2){
        if((tmp & 2) == 2) {
            swapable[a][b + 1] = false;
        }
    }
    if(b > 0){
        if((tmp&1)==1) {
            swapable[a][b - 1] = false;
        }
    }
}

void DFS(int idx, int cnt){
    if(isPossible)
        return;
    if(idx == cnt){
        if(isRight()) {
//            printf("true!\n");
            isPossible = true;
        }
        return;
    }
    for(int i = 0; i < h; i++){
        for(int j = 0; j < n-1; j++){
            if(!swapable[i][j]){
//                printf("%d %d %d\n", i, j, idx);
                int tmp = addSwapable(i, j);
                line_swap(i, j);
                DFS(idx + 1, cnt);
                line_swap(i, j);
                subSwapable(tmp, i, j);
            }
        }
    }
}


int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &h);
    for(int i = 0 ; i < m; i++){
        int tmpa, tmpb;
        scanf("%d %d", &tmpa, &tmpb);
        int trash = addSwapable(tmpa - 1, tmpb - 1);
        lines.push_back(new line(tmpa-1, tmpb-1));
    }

    for(int i = 0; i <= h; i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = j;
        }
    }

    for(int i = 0; i < m; i++){
        line_swap(lines[i]->a, lines[i]->b);
    }

    for(int cnt = 0; cnt < 4; cnt++){
        DFS(0, cnt);
        if(isPossible){
            printf("%d", cnt);
            return 0;
        }
    }

    printf("%d", -1);
    return 0;
}
