//https://www.acmicpc.net/problem/15685

#include <cstdio>
#include <utility>
#include <set>
#include <vector>

using namespace std;

int dist(int x, int y){
    return (x * x) + (y * y);
}

struct myOrder{
    bool operator()(const pair<int, int>& left, const pair<int, int>& right) const{
        if(dist(left.first, left.second) != dist(right.first, right.second))
            return dist(left.first, left.second) > dist(right.first, right.second);
        if(left.first != right.first)
            return left.first > right.first;
        return left.second > right.second;
    }
};

vector<set<pair<int, int>, myOrder>> dragonCurves;

set<pair<int, int>, myOrder> ans;

int n;

pair<int, int> rotate(pair<int, int> p){
    int x = p.first, y = p.second;
    return make_pair(-y, x);

}

pair<int, int> sub(pair<int, int> x, pair<int, int> y){
    return make_pair(x.first - y.first, x.second - y.second);
}

pair<int, int> add(pair<int, int> x, pair<int, int> y){
    return make_pair(x.first + y.first, x.second + y.second);
}

void query(int x, int y, int d, int g){
    pair<int, int> start = make_pair(x, y);
    for(auto it = dragonCurves[g].begin(); it != dragonCurves[g].end(); it++){
        pair<int, int> tmp = *it;
        for(int j = 0; j < ((4 - d) % 4); j++){
            tmp = rotate(tmp);
        }
        ans.insert(add(tmp, start));
    }
}

int findSquare(){
    int ret = 0;
    for(auto it = ans.begin(); it != ans.end(); it++){
        auto a = make_pair(0, 1);
        auto b = make_pair(1, 0);
        auto c = make_pair(1, 1);
        if(ans.find(add(*it, a)) != ans.end() && ans.find(add(*it, b)) != ans.end() && ans.find(add(*it, c)) != ans.end()){
            ret++;
        }
    }
    return ret;
}

void debug(){
    printf("ans_set:\n");
    for(auto it = ans.begin(); it != ans.end(); it++){
        printf("(%d, %d)\n", it->first, it->second);
    }
    printf("\n");
}

int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d", &n);
    set<pair<int, int>, myOrder> zeroGen;
    zeroGen.insert(make_pair(0, 0));
    zeroGen.insert(make_pair(1, 0));
    dragonCurves.push_back(zeroGen);
    pair<int, int> start = make_pair(1, 0);
    for(int i = 1; i <= 10; i++){
        set<pair<int, int>, myOrder> tmpGen;
        for(auto it = dragonCurves[i-1].begin(); it != dragonCurves[i-1].end(); it){
            tmpGen.insert(*it);
            pair<int, int> tmp = *it;
            tmp = sub(tmp, start);
            tmp = rotate(tmp);
            tmp = add(tmp, start);
            tmpGen.insert(tmp);
            if(++it == dragonCurves[i-1].end())
                start = tmp;
        }
        dragonCurves.push_back(tmpGen);
    }

    for(int i = 0; i < n; i++){
        int x, y, d, g;
        scanf("%d %d %d %d", &x, &y, &d, &g);
        query(x, y, d, g);
        //debug();
    }


    printf("%d", findSquare());
    return 0;
}
