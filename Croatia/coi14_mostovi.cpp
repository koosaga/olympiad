#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
typedef pair<lint, lint> pi;
 
int n, m;
 
map<int, int> mp1, mp2;
 
bool query(int sx, int ex, int sy, int ey){
    auto itl = mp1.lower_bound(sx);
    auto itr = mp1.upper_bound(ex);
    if(itl == mp1.end() || itl->first > ex) return 0;
    if(itl->second > ey) return 0;
    itr--;
    if(itr->second < sy) return 0;
    auto ity = mp2.lower_bound(sy);
    if(ity == mp2.end() || ity->first > ey) return 0;
    return 1;
}
 
void ins(int x, int y){
    mp1[x] = y;
    mp2[y] = x;
}
 
set<int> low, high;
void move(int x, int y){
    int sx, sy, ex, ey;
    if(x < y){
        auto t = low.lower_bound(x);
        sx = x, ex = *t;
        auto u = high.lower_bound(y);
        sy = y, ey = *u;
    }
    else{
        auto t = --low.lower_bound(y);
        sx = *t+1, ex = y;
        auto u = --high.lower_bound(x);
        sy = *u+1, ey = x;
    }
    puts(query(sx, ex, sy, ey) ? "DA" : "NE");
}
 
int main(){
    scanf("%d %d",&n,&m);
    low.insert(0);
    low.insert(n);
    high.insert(n);
    high.insert(2*n);
    for(int i=0; i<m; i++){
        char b[5];
        int x, y;
        scanf("%s %d %d",b,&x,&y);
        if(*b == 'B'){
            if(x > y) swap(x, y);
            if(y <= n){
                low.insert(x);
            }
            else{
                high.insert(x);
            }
        }
        if(*b == 'Q'){
            if((x-1) / n == (y-1) / n){
                if(x <= n && x > y){
                    auto u = mp1.lower_bound(x);
                    auto v = low.lower_bound(x);
                    if(u == mp1.end() || (v != low.end() && *v < u->first)) puts("NE");
                    else move(u->second, y);
                }
                else if(x <= n && x <= y){
                    auto t = low.lower_bound(x);
                    puts(y <= *t ? "DA" : "NE");
                }
                else if(x > n && x >= y){
                    auto t = --high.lower_bound(x);
                    puts(*t+1 <= y ? "DA" : "NE");
                }
                else{
                    auto u = mp2.upper_bound(x);
                    auto v = high.lower_bound(x);
                    if(u == mp2.begin()) puts("NE");
                    else{
                        u--;
                        if(v != high.begin() && *--v >= u->first){
                            puts("NE");
                        }
                        else move(u->second, y);
                    }
                }
            }
            else move(x, y);
        }
        if(*b == 'A'){
            if(x > y) swap(x, y);
            ins(x, y);
        }
    }
}