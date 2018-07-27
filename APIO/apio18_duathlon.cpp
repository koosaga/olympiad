#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 100005;
 
int n, m;
int dfn[MAXN], low[MAXN], piv, col, vcnt;
vector<int> gph[MAXN];
vector<int> bcc[MAXN], cmp[MAXN];
 
void dfs(int x, int p){
    dfn[x] = low[x] = ++piv;
    vcnt++;
    for(auto &i : gph[x]){
        if(i == p) continue;
        if(!dfn[i]){
            dfs(i, x);
            low[x] = min(low[x], low[i]);
        }
        else low[x] = min(low[x], dfn[i]);
    }
}
 
void color(int x, int c){
    if(c){
        cmp[x].push_back(c);
        bcc[c].push_back(x);
    }
    for(auto &i : gph[x]){
        if(cmp[i].size()) continue;
        if(low[i] >= dfn[x]){
            col++;
            cmp[x].push_back(col);
            bcc[col].push_back(x);
            color(i, col);
        }
        else{
            color(i, c);
        }
    }
}
 
lint sameOrigin = 0;
lint diffOrigin = 0;
 
lint help(vector<int> &v){
    lint ret = accumulate(v.begin(), v.end(), 0ll);
    ret *= ret;
    for(auto &i : v) ret -= 1ll * i * i;
    return ret;
}
 
int solve(int x){
    int sum = 0;
    vector<int> circomp;
    for(int i=1; i<bcc[x].size(); i++){
        int csum = 0;
        int v = bcc[x][i];
        vector<int> vcomp;
        for(auto &j : cmp[v]){
            if(x == j) continue;
            int val = solve(j);
            vcomp.push_back(val);
            csum += val;
        }
        diffOrigin += help(vcomp);
        circomp.push_back(csum);
        sameOrigin -= 2ll * csum * (bcc[x].size() - 2);
        sum += csum + 1;
    }
    for(int i=0; i<circomp.size(); i++){
        int tmp = sum - bcc[x].size() + 1;
        diffOrigin += 2 * (tmp - circomp[i]);
    }
    diffOrigin += help(circomp);
    circomp.push_back(vcnt - sum);
    diffOrigin += 1ll * (bcc[x].size() - 1) * help(circomp);
    sameOrigin -= 1ll * (bcc[x].size() - 1) * (bcc[x].size() - 2) * (vcnt - bcc[x].size());
    return sum;
}
 
lint Do(int v){
    diffOrigin = sameOrigin = 0;
    vcnt = 0;
    dfs(v, 0);
    int pcol = col;
    color(v, 0);
    vector<int> seq = {1};
    for(int i=pcol + 1; i<=col;i++){
        seq.push_back(bcc[i].size() - 1);
    }
    int tot = accumulate(seq.begin(), seq.end(), 0);
    int pfx = 0;
    for(int i=0; i<seq.size(); i++){
        diffOrigin += 6ll * seq[i] * pfx * (tot - seq[i] - pfx);
        pfx += seq[i];
    }
    sameOrigin = 1ll * vcnt * (vcnt-1) * (vcnt-2) - diffOrigin;
    diffOrigin = 0;
    vector<int> w;
    for(auto &i : cmp[v]){
        w.push_back(solve(i));
    }
    diffOrigin += help(w);
    return diffOrigin + sameOrigin;
}
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    lint sum = 0;
    for(int i=1; i<=n; i++){
        if(!dfn[i]) sum += Do(i);
    }
    cout << sum << endl;
}