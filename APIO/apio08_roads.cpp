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
typedef pair<int, int> pi;
typedef pair<double, double> pr;

struct disj{
    int pa[20005];
    void init(int n){
        for(int i=0; i<=n; i++){
            pa[i] = i;
        }
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        return 1;
    }
}disj1, disj2;

int n, m, k;
vector<pi> s1, s2;
vector<pi> ret;

int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i=0; i<m; i++){
        int s, e, x;
        scanf("%d %d %d",&s,&e,&x);
        if(x == 0) s1.push_back(pi(s, e));
        else s2.push_back(pi(s, e));
    }
    disj2.init(n);
    for(auto &i : s2){
        disj2.uni(i.first, i.second);
    }
    for(auto &i : s1){
        if(disj2.uni(i.first, i.second)){
            ret.push_back(i);
        }
    }
    if(ret.size() > k){
        puts("no solution");
        return 0;
    }
    disj1.init(n);
    for(auto &i : ret){
        disj1.uni(i.first, i.second);
    }
    int rem = k - ret.size();
    for(auto &i : s1){
        if(rem){
            if(disj1.uni(i.first, i.second)){
                ret.push_back(i);
                rem--;
            }
        }
    }
    if(ret.size() != k){
        puts("no solution");
        return 0;
    }
    for(auto &i : ret){
        printf("%d %d 0\n",i.first, i.second);
    }
    for(auto &i : s2){
        if(disj1.uni(i.first, i.second)){
            printf("%d %d 1\n",i.first, i.second);
        }
    }
}
