#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h> 
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int cell[7][2] = {{1, 2}, {4, 8}, {7, 11}, {13, 14}, {16, 20},{19, 23}, {25, 26}};
int occu[10][7] = {
    {1, 1, 1, 0, 1, 1, 1}, {0, 0, 1, 0, 0, 1, 0}, 
    {1, 0, 1, 1, 1, 0, 1}, {1, 0, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0}, {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 1, 1}};

int n;
string str[705];
char ret[8][22];
bool ok[1440];

char tab[1440][8][22];
char full[8][22];

void set_table(int t){
    for(int i=0; i<7; i++){
        for(int j=0; j<21; j++){
            tab[t][i][j] = '.';
        }
    }
    tab[t][2][10] = 'X';
    tab[t][4][10] = 'X';
    int p[4] = {0, 5, 12, 17};
    int q[4] = {(t / 60) / 10, (t / 60) % 10, (t % 60) / 10, (t % 60) % 10};
    for(int i=0; i<4; i++){
        int num = q[i];
                if(num == 0 && i == 0) continue;

        for(int j=0; j<7; j++){
            if(occu[num][j]){
                for(int k=0; k<2; k++){
                    int tt = cell[j][k];
                    tab[t][tt / 4][tt % 4 + p[i]] = 'X';
                }
            }
        }
    }
}
void set_full(){
    for(int i=0; i<7; i++){
        for(int j=0; j<21; j++){
            full[i][j] = '.';
        }
    }
    full[2][10] = 'X';
    full[4][10] = 'X';
    int p[4] = {0, 5, 12, 17};
    int q[4] = {8, 8, 8, 8};
    for(int i=0; i<4; i++){
        int num = q[i];
        for(int j=0; j<7; j++){
            if(occu[num][j]){
                for(int k=0; k<2; k++){
                    int tt = cell[j][k];
                    full[tt / 4][tt % 4 + p[i]] = 'X';
                }
            }
        }
    }
}

bool check(pi p, int q){
    for(int i=0; i<n; i++){
        char p1 = tab[(i + q)%1440][p.first][p.second];
        char p2 = str[7 * i + p.first][p.second];
        if(p1 != p2) return 0;
    }
    return 1;
    // Q time interval, does p match??
}

int main(){
    cin >> n;
    for(int i=0; i<7*n; i++){
        cin >> str[i];
    }
    for(int i=0; i<1440; i++){
        ok[i] = 1;
        set_table(i);
    }
    set_full();
    vector<pi> fuex;
    for(int i=0; i<7; i++){
        for(int j=0; j<21; j++){
            if(full[i][j] == '.'){
                ret[i][j] = '.';
                continue;
            }
            int cnt = 0;
            for(int k=0; k<n; k++){
                if(str[k * 7 + i][j] == '.'){
                    cnt++;
                }
            }
            if(cnt == 0 || cnt == n){
                fuex.emplace_back(i, j);
            }
            else{
                ret[i][j] = 'W';
                for(int k=0; k<1440; k++){
                    if(!ok[k]) continue;
                    bool good = 1;
                    for(int l=0; l<n; l++){
                        if(str[l * 7 + i][j] != tab[(k + l) % 1440][i][j]){
                            ok[k] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(count(ok, ok + 1440, true) == 0){
        puts("impossible");
        return 0;
    }
    for(auto &i : fuex){
        bool exi = 0;
        for(int j=0; j<1440; j++){
            if(ok[j]){
                if(check(i, j)){
                    exi = 1;
                    break;
                }
            }
        }
        if(exi) ret[i.first][i.second] = '?';
        else if(str[i.first][i.second] == 'X') ret[i.first][i.second] = '1';
        else ret[i.first][i.second] = '0';
    }
    for(int i=0; i<7; i++) puts(ret[i]);
}