//https://www.acmicpc.net/problem/19238

#include <cstdio>
#include <climits>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int n, m, k;
int map[21][21];
int people[21][21];
bool checked[21][21];
int step[21][21];
int t_x, t_y;
queue<pair<int, int>> q;

int battery;
struct person{
    int s_x;
    int s_y;
    int e_x;
    int e_y;
    person(int s_x, int s_y, int e_x, int e_y):s_x(s_x), s_y(s_y), e_x(e_x), e_y(e_y){

    }
    bool endpoint(int x, int y){
        return e_x == x && e_y == y;
    }
};

vector<person*> persons;

bool InRange(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool CanGo(int x, int y){
    return InRange(x, y) && map[x][y] == 0 && !checked[x][y];
}

void init(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            step[i][j] = 0;
            checked[i][j] = false;
        }
    }
}

void Push(int x, int y, int new_step){
    q.push(make_pair(x, y));
    checked[x][y] = true;
    step[x][y] = new_step;
}

pair<int, int> start_BFS(){
    int min_dist = INT_MAX;
    while(!q.empty()){
        int x = q.front().first, y = q.front().second;
        q.pop();
        if(step[x][y] >= min_dist)
            continue;
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        for(int dir = 0; dir < 4; dir++){
            int nx = x + dx[dir], ny = y + dy[dir];
            if(CanGo(nx, ny)){
                Push(nx, ny, step[x][y] + 1);
                if(people[nx][ny] != 0){
                    min_dist = step[x][y] + 1;
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(step[i][j] == min_dist && people[i][j] != 0){
                return make_pair(people[i][j] - 1, min_dist);
            }
        }
    }

    return make_pair(-1, -1);
}

int end_BFS(int idx){
    int min_dist = INT_MAX;
    while(!q.empty()){
        int x = q.front().first, y = q.front().second;
        q.pop();
        if(step[x][y] >= min_dist)
            continue;
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        for(int dir = 0; dir < 4; dir++){
            int nx = x + dx[dir], ny = y + dy[dir];
            if(CanGo(nx, ny)){
                Push(nx, ny, step[x][y] + 1);
                if(persons[idx]->endpoint(nx, ny)){
                    min_dist = step[x][y] + 1;
                }
            }
        }
    }
    return (min_dist==INT_MAX)?-1:min_dist;
}

int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d ", &map[i][j]);
        }
    }
    battery = k;
    scanf("%d %d", &t_x, &t_y);
    t_x--;
    t_y--;
    for(int i = 0; i < m; i++){
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        persons.push_back(new person(a-1,b-1,c-1,d-1));
        people[a-1][b-1] = i+1;
    }

    int drive_cnt = 0;
    bool isPossible = true;

    while(drive_cnt < m){
        init();
        pair<int,int> p;
        if(people[t_x][t_y] == 0) {
            Push(t_x, t_y, 0);
            p = start_BFS();
        } else {
            p = make_pair(people[t_x][t_y] - 1, 0);
        }
        battery -= p.second;
        if(battery <= 0 || p.first == -1){
            isPossible = false;
            break;
        }
        t_x = persons[p.first]->s_x;
        t_y = persons[p.first]->s_y;
        people[t_x][t_y] = 0;

       // printf("%d\n", battery);
        init();
        Push(t_x, t_y, 0);
        int tmp = end_BFS(p.first);
        t_x = persons[p.first]->e_x;
        t_y = persons[p.first]->e_y;
        battery -= tmp;
        if(battery < 0 || tmp == -1){
            isPossible = false;
            break;
        }
       // printf("%d\n", battery);
        battery += 2*tmp;
        drive_cnt++;
       // printf("%d\n", battery);
    }

    printf("%d", (isPossible)?battery:-1);
    return 0;
}
