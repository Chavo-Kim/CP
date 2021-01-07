#include <cstdio>
#include <climits>
#include <vector>

using namespace std;

int n, m;
int map[9][9];
int cam;
int ans = INT_MAX;

struct camera{
    int x;
    int y;
    int dir;
    int idx;
    camera(int x, int y, int idx):x(x), y(y), idx(idx){
        dir = 0;
    }
};

vector<camera*> cameras;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void init(bool (*tmp)[9]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            tmp[i][j] = false;
        }
    }
}

bool InRange(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}

bool CanGo(int x, int y){
    return InRange(x, y) && map[x][y] != 6;
}

void color(camera* _camera, bool (*tmp)[9], int dir){
    int x = _camera->x, y = _camera->y;
    do{
        tmp[x][y] = true;
        x = x + dx[dir], y = y + dy[dir];
    }while (CanGo(x, y));
}

int howTrue(bool (*tmp)[9]){
    int ret = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!tmp[i][j] && map[i][j] != 6) ret++;
        }
    }
    return ret;
};

int simul(bool (*tmp)[9]){
    for(int num = 0; num < cam; num++){
        int idx = cameras[num]->idx;
        int dir = cameras[num]->dir;
        if(idx==0){
            color(cameras[num], tmp, dir);
        } else if(idx == 1){
            color(cameras[num], tmp, dir);
            color(cameras[num], tmp, (dir + 2)%4);
        } else if(idx == 2){
            color(cameras[num], tmp, dir);
            color(cameras[num], tmp, (dir + 1)%4);
        } else if(idx == 3){
            color(cameras[num], tmp, dir);
            color(cameras[num], tmp, (dir + 1)%4);
            color(cameras[num], tmp, (dir + 2)%4);
        } else if(idx == 4){
            color(cameras[num], tmp, dir);
            color(cameras[num], tmp, (dir + 1)%4);
            color(cameras[num], tmp, (dir + 2)%4);
            color(cameras[num], tmp, (dir + 3)%4);
        }
    }

    return howTrue(tmp);
}

void DFS(int cnt){
    if(cnt == cam){
        bool tmp[9][9];
        init(tmp);
        int ret = simul(tmp);
        if(ret < ans) {
            ans = ret;
        }
        return;
    }

    for(int dir = 0; dir < 4; dir++){
        cameras[cnt]->dir = dir;
        DFS(cnt+1);
    }
}

int main() {
    freopen("../input.txt","r", stdin);
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d ", &map[i][j]);
            if(map[i][j] < 6 && map[i][j] > 0) {
                cam++;
                cameras.push_back(new camera(i, j, map[i][j]-1));
            }
        }
    }
    DFS(0);
    printf("%d", ans);
    return 0;
}
