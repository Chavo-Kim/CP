//https://www.acmicpc.net/problem/16236

#include <cstdio>
#include <cmath>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

int n;
int map[21][21];
int step[21][21];
bool checked[21][21];
int ans;
queue<pair<int, int>> q;

struct shark{
    int x;
    int y;
    int level;
    int cnt;
    shark(int x, int y, int level):x(x), y(y), level(level){
        cnt = 0;
    }
    void update(int x, int y){
        this->x = x;
        this->y = y;
    }
    void levelup(){
        if(this->cnt == level){
            this->level++;
            this->cnt = 0;
        }
    }
    void eat(int x, int y){
        this->cnt++;
        levelup();
//        printf("(%d, %d) level %d eat!\n", x, y, map[x][y]);
//        printf("level is %d\n", this->level);
    }
};

void debug(){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

shark* _shark = new shark(0, 0, 2);

bool InRange(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool CanGo(int x, int y){
    return InRange(x, y) && (map[x][y] <= _shark->level) && (!checked[x][y]);
}

void Push(int x, int y, int new_step){
    q.push(make_pair(x, y));
    checked[x][y] = true;
    step[x][y] = new_step;
}

bool canEat(int x, int y){
    return InRange(x, y) && map[x][y] > 0 && _shark->level > map[x][y];
}

int BFS(){
    int min_cnt = INT_MAX;
    while(!q.empty()){
        int x = q.front().first, y = q.front().second;
        q.pop();
        if(step[x][y] >= min_cnt){
            continue;
        }
        int dx[4] = {0, 0, 1, -1}; int dy[4] = {1, -1, 0, 0};
        for(int dir = 0; dir < 4; dir++){
            int nx = x + dx[dir], ny = y + dy[dir];
            if(CanGo(nx, ny)){
                Push(nx, ny, step[x][y] + 1);
                if(canEat(nx, ny)){
                    min_cnt = step[x][y] + 1;
                }
            }
        }
    }
    if(min_cnt == INT_MAX){
        return -1;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(step[i][j] == min_cnt && canEat(i, j)){
                _shark->eat(i, j);
                map[_shark->x][_shark->y] = 0;
                map[i][j] = 9;
                _shark -> update(i, j);
                return min_cnt;
            }
        }
    }
}

void init(){
    for(int i = 0; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            checked[i][j] = false;
            step[i][j] = 0;
        }
    }
}

int simul(){
    init();
    Push(_shark->x, _shark->y, 0);
    return BFS();
}

int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &map[i][j]);
            if(map[i][j] == 9){
                _shark->update(i, j);
            }
        }
    }



    while(true){
        int tmp = simul();
        if(tmp == -1){
            break;
        } else {
            ans += tmp;
        }
//        printf("ans :%d\n", ans);
//        debug();
    }

    printf("%d", ans);

    return 0;
}
