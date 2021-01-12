#include <cstdio>
#include <utility>

using namespace std;

int n, m, k;

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int mass_map[51][51];
int speed_map[51][51];
int dir_map[51][51];
int cnt_map[51][51];

int fircnt;

struct fireball{
    int x;
    int y;
    int b;
    int s;
    int d;
    fireball(int r, int c, int b, int s, int d):x(r), y(c), b(b), s(s), d(d){

    }
    void update(int r, int c, int b, int s, int d){
        this->x = r;
        this->y = c;
        this->b = b;
        this->s = s;
        this->d = d;
    }
};

fireball* fireballs[100001];

void init(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mass_map[i][j] = 0;
            speed_map[i][j] = 0;
            dir_map[i][j] = 0;
            cnt_map[i][j] = 0;

        }
    }
}

bool InRange(int x, int y){
    return x >= 0 && x < n && y < n && y >= 0;
}

pair<int, int> makeInRange(int x, int y){
    if(InRange(x, y))
        return make_pair(x, y);
    int curr_x = x, curr_y = y;
    while(curr_x < 0){
        curr_x += n;
    }
    while(curr_y < 0){
        curr_y += n;
    }
    return make_pair(curr_x % n, curr_y % n);
}

int getDir(int md, int cd){
    if(md == 0){
        return cd + 1;
    } else {
        if(((md - 1) % 2) == (cd % 2))
            return md;
        else
            return -1;
    }

}

void moveFire(){
    for(int i = 0; i < fircnt; i++){
        int nx = fireballs[i]->x + (dx[fireballs[i]->d] * fireballs[i]->s);
        int ny = fireballs[i]->y + (dy[fireballs[i]->d] * fireballs[i]->s);
        pair<int, int> pos = makeInRange(nx, ny);
        mass_map[pos.first][pos.second] += fireballs[i]->b;
        speed_map[pos.first][pos.second] += fireballs[i]->s;
        dir_map[pos.first][pos.second] = getDir(dir_map[pos.first][pos.second], fireballs[i]->d);
        cnt_map[pos.first][pos.second]++;
    }
}

int seperate(int x, int y, int cnt){
    int curr_cnt = cnt;
    if(mass_map[x][y] / 5 == 0)
        return curr_cnt;
    int mass = mass_map[x][y] / 5;
    int speed = speed_map[x][y] / cnt_map[x][y];
    if(dir_map[x][y] == -1){
        for(int i = 1; i < 8; i += 2){
            if(curr_cnt < fircnt)
                fireballs[curr_cnt++]->update(x, y, mass, speed, i);
            else
                fireballs[curr_cnt++] = new fireball(x, y, mass, speed, i);
        }
    } else {
        for(int i = 0; i < 8; i += 2){
            if(curr_cnt < fircnt)
                fireballs[curr_cnt++]->update(x, y, mass, speed, i);
            else
                fireballs[curr_cnt++] = new fireball(x, y, mass, speed, i);
        }
    }
    return curr_cnt;
}

void seperateFire(){
    int cnt = 0;
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n; j++){
            if(cnt_map[i][j] == 0)
                continue;
            if(cnt_map[i][j] == 1){
                if(cnt < fircnt)
                    fireballs[cnt++]->update(i, j, mass_map[i][j], speed_map[i][j], dir_map[i][j] - 1);
                else{
                    fireballs[cnt++] = new fireball(i, j, mass_map[i][j], speed_map[i][j], dir_map[i][j] - 1);
                }
                continue;
            }
            cnt = seperate(i, j, cnt);
        }
    }
    fircnt = cnt;
}

void query(){
    init();
    moveFire();
    seperateFire();
}

int ans(){
    int ret = 0;
    for(int i = 0 ; i < fircnt; i++){
        ret += fireballs[i]->b;
    }
    return ret;
}

int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for(int i= 0; i < m; i++){
        int r, c, b, s, d;
        scanf("%d %d %d %d %d", &r, &c, &b, &s, &d);
        fireballs[i] = new fireball(r -1 , c- 1, b, s, d);
    }
    fircnt = m;
    for(int i = 0; i < k; i++){
        query();
    }
    printf("%d", ans());
    return 0;
}
