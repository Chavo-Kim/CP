//https://open.kattis.com/contests/mcpc19open/problems/basketballoneonone

#include <bits/stdc++.h>

using namespace std;

int main() {
    //freopen("../input.txt", "r", stdin);
    char str[201];
    int a_score = 0, b_score = 0;
    scanf("%s", str);
    for(int i = 0; str[i] != 0; i+=2){
        if(str[i] == 'A'){
            a_score += str[i+1] - '0';
        } else {
            b_score += str[i+1] - '0';
        }
    }
    if(a_score > b_score)
        printf("A");
    else
        printf("B");
    return 0;
}
