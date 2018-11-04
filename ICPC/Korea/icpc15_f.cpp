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

vector<int> gph[100005], rev[100005];
vector<int> dfn;

int n, m;
int vis[100005], comp[100005], p;
bool sol[100005];

void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    for(auto &i : gph[x]){
        dfs(i);
    }
    dfn.push_back(x);
}

void rdfs(int x, int p){
    if(comp[x]) return;
    comp[x] = p;
    for(auto &i : rev[x]){
        rdfs(i, p);
    }
}

int dep[100005], par[100005], vis2[100005];
vector<pi> edg;

void dfs2(int x){
    vis2[x] = 1;
    for(auto &i : gph[x]){
        if(comp[i] != comp[x]) continue;
        edg.emplace_back(x, i);
        if(!vis2[i]){
            par[i] = x;
            dep[i] = dep[x] + 1;
            dfs2(i);
        }
    }
}

int getlca(int x, int y){
    if(x == y) return y;
    if(dep[x] == dep[y]) return getlca(par[x], par[y]);
    if(dep[x] < dep[y]) return getlca(x, par[y]);
    return getlca(par[x], y);
}

int rpar[100005], rvis[100005], rdist[100005];

void dfs3(int x){
    rvis[x] = 1;
    for(auto &i : gph[x]){
        if(!rvis[i]){
            rpar[i] = x;
            rdist[i] = rdist[x] + 1;
            dfs3(i);
        }
    }
}

void report(vector<int> v){
    set<int> s;
    int chk = -1;
    for(int i=0; i<v.size(); i++){
        if(s.find(v[i]) != s.end()){
            chk = i;
            break;
        }
        s.insert(v[i]);
    }
    if(chk == -1){
        printf("1\n%d\n",v.size());
        for(auto &i : v){
            printf("%d\n",i);
        }
        return;
    }
    rotate(v.begin(), v.begin() + chk, v.end());
    if(chk % 2 == 0){
        vector<int> u;
        for(int j=chk; j<v.size(); j++){
            u.push_back(v[j]);
        }
        report(u);
    }
    else{
        vector<int> u;
        for(int j=0; j<chk; j++){
            u.push_back(v[j]);
        }
        report(u);
    }
}

bool go(int x){
    edg.clear();
    dfs2(x);
    for(auto &i : edg){
        if(dep[i.first] % 2 == dep[i.second] % 2){
            int t = getlca(i.first, i.second);
            memset(rvis, 0, sizeof(rvis));
            memset(rdist, 0, sizeof(rdist));
            dfs3(i.second);
            vector<int> ret;
            if((rdist[t] + dep[i.first] + 1 - dep[t]) % 2 == 1){
                for(int j=t; j!=i.second; j=rpar[j]){
                    ret.push_back(j);
                }
                ret.push_back(i.second);
                for(int j=i.first; j!=t; j=par[j]){
                    ret.push_back(j);
                }
                reverse(ret.begin(), ret.end());
            }
            else{
                int cnt = 0;
                for(int j=t; j!=i.second; j=rpar[j]){
                    if((dep[j] - dep[t] + cnt) % 2 == 1){
                        for(int k=t; k!=j; k=rpar[k]){
                            ret.push_back(k);
                        }
                        for(int k=j; k!=t; k=par[k]){
                            ret.push_back(k);
                        }
                        reverse(ret.begin(), ret.end());
                        break;
                    }
                    cnt++;
                }
            }
            report(ret);
            return 1;
        }
    }
    return 0;
}

void solve(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        rev[e].push_back(s);
    }
    for(int i=1; i<=n; i++){
        if(!vis[i]) dfs(i);
    }
    reverse(dfn.begin(), dfn.end());
    for(auto &i : dfn){
        if(!comp[i]) rdfs(i, ++p);
    }
    for(int i=1; i<=n; i++){
        if(!sol[comp[i]]){
            sol[comp[i]] = 1;
            if(go(i)){
                return;
            }
        }
    }
    puts("-1");
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
        // fuck this
        for(int i=1; i<=n; i++){
            gph[i].clear();
            rev[i].clear();
        }
        dfn.clear();
        memset(comp, 0, sizeof(comp));
        memset(sol, 0, sizeof(sol));
        memset(vis, 0, sizeof(vis));
        memset(vis2, 0, sizeof(vis2));
        memset(dep, 0, sizeof(dep));
        memset(par, 0, sizeof(par));
        p = 0;
    }
}