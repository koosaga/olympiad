#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 50005;

vector<int> gph[MAXN];
vector<int> bcc[MAXN];
vector<int> cmp[MAXN];

int dfn[MAXN], low[MAXN], piv;
int n, m, k, c;

void dfs(int x, int p){
    dfn[x] = low[x] = ++piv;
    for(auto &i : gph[x]){
        if(i == p) continue;
        if(!dfn[i]){
            dfs(i, x);
            low[x] = min(low[x], low[i]);
        }
        else low[x] = min(low[x], dfn[i]);
    }
}

void color(int x, int p){
    if(p){
        bcc[p].push_back(x);
        cmp[x].push_back(p);
    }
    for(auto &i : gph[x]){
        if(cmp[i].size()) continue;
        if(low[i] >= dfn[x]){
            bcc[++c].push_back(x);
            cmp[x].push_back(c);
            color(i, c);
        }
        else color(i, p);
    }
}

void halt(){
    puts("-1");
    exit(0);
}

vector<vector<int>> ans;
int stk[MAXN], cnt[MAXN], sz;

vector<int> solve(int c){
    vector<vector<int>> cv;
    int rn = 0;
    for(int i=1; i<bcc[c].size(); i++){
        int x = bcc[c][i];
        vector<int> v;
        v.push_back(x);
        for(auto &j : cmp[x]){
            if(j == c) continue;
            auto y = solve(j);
            if(y.size() > v.size()) swap(y, v);
            for(auto &ww : y) v.push_back(ww);
        }
        if(v.size() > k) halt();
        cv.push_back(v);
        rn += v.size();
    }
    rn = (k - rn % k) % k;
    if(rn == 0) rn = k;
    int rootup = rn;
    stk[0] = rn;
    for(int i=0; i<cv.size(); i++){
        rn += cv[i].size();
        stk[i+1] = rn;
    }
    int tot = rn / k;
    if(tot == 1){
        vector<int> ret;
        for(auto &i : cv){
            if(ret.size() < i.size()) swap(ret, i);
            for(auto &j : i) ret.push_back(j);
        }
        return ret;
    }
    int modpos = -1;
    for(int i=0; i<bcc[c].size(); i++){
        cnt[stk[i] % k]++;
        if(cnt[stk[i] % k] == tot){
            modpos = stk[i] % k;
        }
    }
    if(modpos == -1) halt();
    for(int i=0; i<bcc[c].size(); i++){
        cnt[stk[i] % k]--;
    }
    vector<int> ret;
    for(int i=0; i<bcc[c].size(); i++){
        if(modpos == stk[i] % k){
            vector<int> nxt;
            int lef = k;
            int pos = i;
            while(pos < cv.size() && lef){
                lef -= cv[pos].size();
                if(nxt.size() < cv[pos].size()) swap(nxt, cv[pos]);
                for(auto &j : cv[pos]) nxt.push_back(j);
                pos++;
            }
            if(nxt.size() == k){
                ans.push_back(nxt);
            }
            else{
                lef -= rootup;
                int pos = 0;
                while(pos < cv.size() && lef){
                    lef -= cv[pos].size();
                    if(nxt.size() < cv[pos].size()) swap(nxt, cv[pos]);
                    for(auto &j : cv[pos]) nxt.push_back(j);
                    pos++;
                }
                ret = nxt;
            }
        }
    }
    return ret;
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    k = n / k;
    for(int i=0; i<m; i++){
        int x, p;
        scanf("%d %d",&x, &p);
        for(int j=1; j<x; j++){
            int w;
            scanf("%d",&w);
            gph[p].push_back(w);
            gph[w].push_back(p);
            p = w;
        }
    }
    dfs(1, 0);
    color(1, 0);
    vector<int> aux = {1};
    for(auto &i : cmp[1]){
        auto k = solve(i);
        for(auto &j : k){
            aux.push_back(j);
        }
    }
    if(aux.size() != k) halt();
    ans.push_back(aux);
    for(auto &i : ans){
        sort(i.begin(), i.end());
        for(auto &j : i) printf("%d ", j);
        puts("");
    }
}
