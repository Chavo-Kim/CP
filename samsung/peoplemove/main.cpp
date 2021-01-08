//https://www.acmicpc.net/problem/16234

#include <cstdio>
#include <queue>
#include <cmath>
#include <utility>

using namespace std;

int n, l, r;
queue<pair<int, int>> q;
int map[51][51];
bool checked[51][51];

bool InRange(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool CanGo(int x, int y, int val){
    return InRange(x, y) && (abs(map[x][y] - val) >= l && abs(map[x][y] - val) <= r) && !checked[x][y];
}

void debug(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void init(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            checked[i][j] = false;
        }
    }
}

void Push(int x, int y){
    checked[x][y] = true;
    q.push(make_pair(x, y));
}

bool BFS(int x, int y){
    int ret = 1;
    int sum = map[x][y];
    vector<pair<int, int>> towns;
    towns.push_back(make_pair(x, y));
    while(!q.empty()){
        int curr_x = q.front().first, curr_y = q.front().second;
        q.pop();
        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};
        for(int dir = 0; dir < 4; dir++){
            int nx = curr_x + dx[dir], ny = curr_y + dy[dir];
            if(CanGo(nx, ny, map[curr_x][curr_y])){
                Push(nx, ny);
                ret++;
                sum += map[nx][ny];
                towns.push_back(make_pair(nx, ny));
            }
        }
    }
    int renew = sum / ret;
    for(int i = 0; i < towns.size(); i++){
        map[towns[i].first][towns[i].second] = renew;
    }
    return towns.size() != 1;
}

int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d %d %d", &n, &l, &r);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d ", &map[i][j]);
        }
    }
    int cnt = 0;
    bool move = false;
    while(cnt <= 2000) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!checked[i][j]) {
                    Push(i, j);
                    if(BFS(i, j))
                        move = true;
                }
            }
        }
        if(move){
            move = false;
        } else {
            break;
        }
        init();
        cnt++;
        //debug();
    }
    printf("%d", cnt);
    return 0;
}
