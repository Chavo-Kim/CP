//https://www.acmicpc.net/problem/17143

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int r, c;
int m;
int ans;
int map[101][101];
int tmp[101][101];
int dx[4]={-1, 1, 0, 0};
int dy[4]={0, 0, 1, -1};
int conv[4]={1, 0, 3, 2};

struct shark{
    int x;
    int y;
    int s;
    int d;
    int big;
    shark(int x, int y, int s, int d, int big):x(x), y(y), s(s), d(d), big(big){

    }
    void update(int x, int y){
        this->x = x;
        this->y = y;
    }
};

vector<shark*> sharks;

bool comp_shark(shark* l, shark* r){
    return l->big < r->big;
}

bool rInRange(int x){
    return x >= 0 && x < r;
}

bool cInRange(int y){
    return y >= 0 && y < c;
}

int fishing(int j){
    for(int i = 0; i < r; i++){
        if(map[i][j] != 0){
            int ret = map[i][j];
            map[i][j] = 0;
            return ret;
        }
    }
    return 0;
}

void getPosition(shark* _shark){
    int nx = _shark->x + (dx[_shark->d] * _shark->s) , ny = _shark->y + (dy[_shark->d] * _shark->s);
    if(!rInRange(nx)){
        if(nx < 0){
            nx = abs(nx) - 1;
        } else {
            nx = abs(nx - r);
        }
        if((nx / (r - 1)) % 2 == 0){
            nx = (nx % (r - 1));
            if(_shark->d == 1){
                _shark->update(r-nx-2, ny);
                tmp[r-nx-2][ny] = _shark->big;
                _shark->d = conv[_shark->d];
            } else {
                _shark->update(nx+1, ny);
                tmp[nx+1][ny] = _shark->big;
                _shark->d = conv[_shark->d];
            }
        } else {
            nx = (nx % (r - 1));
            if(_shark->d == 1){
                _shark->update(nx+1, ny);
                tmp[nx+1][ny] = _shark->big;

            } else {
                _shark->update(r-nx-2, ny);
                tmp[r-nx-2][ny] = _shark->big;
            }
        }
    } else if(!cInRange(ny)){
        if(ny < 0){
            ny = abs(ny) - 1;
        } else {
            ny = abs(ny - c);
        }
        if((ny / (c - 1)) % 2 == 0){
            ny = ny % (c - 1);
            if(_shark->d == 2){
                _shark->update(nx, c-ny-2);
                tmp[nx][c-ny-2] = _shark->big;
                _shark->d = conv[_shark->d];
            } else {
                _shark->update(nx, ny+1);
                tmp[nx][ny+1] = _shark->big;
                _shark->d = conv[_shark->d];
            }
        } else {
            ny = ny % (c - 1);
            if(_shark->d == 2){
                _shark->update(nx, ny+1);
                tmp[nx][ny+1] = _shark->big;

            } else {
                _shark->update(nx, c-ny-2);
                tmp[nx][c-ny-2] = _shark->big;
            }
        }
    } else {
        _shark->update(nx, ny);
        tmp[nx][ny] = _shark->big;
    }
}

void init(){
    for(int i = 0; i < r ; i++){
        for(int j = 0 ; j < c ; j++){
            tmp[i][j] = 0;
        }
    }
}

void paste(){
    for(int i = 0; i < r ; i++){
        for(int j = 0 ; j < c ; j++){
            map[i][j] = tmp[i][j];
        }
    }
}

void move(){
    for(int i = 0; i < m; i++){
        int x = sharks[i]->x,
        y = sharks[i]->y,
        big = sharks[i]->big;
        if (map[x][y] != big) continue;
        getPosition(sharks[i]);
    }
}

void debug(){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int simul(int j){
   int ret = fishing(j);
   init();
   move();
   paste();
   return ret;
}

int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d %d %d", &r, &c, &m);
    for(int i = 0; i < m; i++){
        int x, y, s, d, z;
        scanf("%d %d %d %d %d", &x, &y, &s, &d, &z);
        sharks.push_back(new shark(x-1, y-1, s, d-1, z));
        map[x-1][y-1] = z;
    }
    sort(sharks.begin(), sharks.end(), comp_shark);
    for(int j = 0; j < c; j++){
        //debug();
        ans += simul(j);
    }
    //debug();
    printf("%d", ans);
    return 0;
}
