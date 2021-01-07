//https://www.acmicpc.net/problem/15684

#include <cstdio>
#include <vector>

using namespace std;

int n, m, h;

struct line{
    int a;
    int b;
    line(int a, int b):a(a), b(b){

    }
};

vector<line*> lines;

bool comp(line* a, line* b){
    return a->a < b->a;
}

int main() {
    scanf("%d %d %d", &n, &m, &h);
    for(int i = 0 ; i < m; i++){
        int tmpa, tmpb;
        scanf("%d %d", tmpa, tmpb);
        lines.push_back(new line(tmpa, tmpb));
    }
    sort()
    return 0;
}
