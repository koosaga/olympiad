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

int n;
char str[100];
int a[11];

struct disj{
    int pa[22];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    void uni(int p, int q){
        pa[find(p)] = find(q);
    }
}disj;

int ind[22];
bool vis[22];
vector<int> dfn;
vector<int> graph[22];

void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    for(auto &i : graph[x]){
        dfs(i);
    }
    dfn.push_back(x);
}

int main(){
    scanf("%d %s",&n,str);
    disj.init(n);
    int p = 0;
    for(int i=1; i<=n; i++){
        for(int j=i; j<=n; j++){
            if(str[p] == '0'){
                disj.uni(i-1, j);
            }
            p++;
        }
    }
    p = 0;
    for(int i=1; i<=n; i++){
        for(int j=i; j<=n; j++){
            int src = disj.find(i-1);
            int snk = disj.find(j);
            if(str[p] == '+'){
                graph[src].push_back(snk);
            }
            else if(str[p] == '-'){
                graph[snk].push_back(src);
            }
            p++;
        }
    }
    for(int i=0; i<=n; i++){
        if(disj.find(i) != i) continue;
        if(!vis[i]) dfs(i);
    }
    p = 1;
    reverse(dfn.begin(), dfn.end());
    for(auto &i : dfn){
        a[i] = p++;
    }
    int off = a[disj.find(0)];
    for(int i=0; i<=n; i++){
        if(disj.find(i) != i) continue;
        a[i] -= off;
    }
    for(int i=0; i<=n; i++){
        a[i] = a[disj.find(i)];
    }
    for(int i=1; i<=n; i++){
        printf("%d ",a[i] - a[i-1]);
    }
}