#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;
 
vector<pi> graph[100005];
int n;
bool vis[100005];
 
lint ret;
 
vector<int> proc;
int size[100005], msize[100005];
 
int dfs(int x, int pa){
    if(vis[x]) return 0;
    size[x] = 1;
    msize[x] = 0;
    proc.push_back(x);
    for(auto &i : graph[x]){
        if(i.second == pa) continue;
        int t = dfs(i.second,x);
        size[x] += t;
        msize[x] = max(t,msize[x]);
    }
    return size[x];
}
 
int get_center(int x){
    proc.clear();
    dfs(x,0);
    int maxp = -1, maxv = 1e9;
    for (auto &i : proc){
        int tmp = max(msize[i], (int)proc.size() - size[i]);
        if(maxv > tmp){
            maxv = tmp;
            maxp = i;
        }
    }
    return maxp;
}
 
vector<int> tree[100005];
int piv;
 
queue<int> que, par, val;
int nodev[100005], num[100005];
 
void make_tree(int x){
    for(int i=0; i<=piv; i++){
        tree[i].clear();
        nodev[i] = 0;
    }
    piv = 0;
    que.push(x);
    par.push(-1);
    val.push(0);
    while(!que.empty()){
        int qf = que.front(), pf = par.front(), vf = val.front();
        que.pop(), par.pop(), val.pop();
        piv++;
        num[qf] = piv;
        nodev[piv] = vf;
        if(pf != -1){
            tree[num[pf]].push_back(piv);
        }
        for(auto &i : graph[qf]){
            if(vis[i.second]) continue;
            if(i.second == pf) continue;
            que.push(i.second);
            par.push(qf);
            val.push(vf + i.first);
        }
    }
}
 
int tsize[100005], dfn[100005], rdfn[100005], piv2;
int dlow[100005], dlow2[100005];
int low[100005], low2[100005];
 
int dfs2(int x, int pa){
    dfn[x] = ++piv2;
    rdfn[piv2] = x;
    tsize[x] = 1;
    for(auto &i : tree[x]){
        if(i == pa) continue;
        tsize[x] += dfs2(i, x);
    }
    return tsize[x];
}
 
lint solve2(vector<pi> &v){
    sort(v.begin(), v.end());
    lint ret = 0;
    for(int i=0; i<v.size(); i++){
        if(v[i].first < 0) continue;
        if(v[i].first == 0 && v[i].second == 0){
            ret += (int)(upper_bound(v.begin(), v.end(), pi(0, 1)) - lower_bound(v.begin(), v.end(), pi(0, 1)));
        }
        if(v[i].first == 0 && v[i].second == 1){
            ret += (int)(upper_bound(v.begin(), v.end(), pi(0, 1)) - (v.begin() + i + 1));
        }
        if(v[i].first && v[i].second == 0){
            ret += (int)(upper_bound(v.begin(), v.end(), pi(-v[i].first, 1)) - lower_bound(v.begin(), v.end(), pi(-v[i].first, 1)));
        }
        if(v[i].first && v[i].second == 1){
            ret += (int)(upper_bound(v.begin(), v.end(), pi(-v[i].first, 1)) - lower_bound(v.begin(), v.end(), pi(-v[i].first, 0)));
        }
    }
    return ret;
}
 
vector<pi> paint;
 
void solve(int x){
    int t = get_center(x);
    vis[t] = 1;
    x = t;
    make_tree(x);
    piv2 = 0;
    dfs2(1,0);
    fill(low, low + piv + 1, 0);
    fill(low2, low2 + piv + 1, 0);
    fill(dlow, dlow + piv + 1, 0);
    fill(dlow2, dlow2 + piv + 1, 0);
    paint.clear();
    for(int i=1; i<=piv; i++){
        paint.push_back(pi(nodev[i], dfn[i]));
    }
    sort(paint.begin(), paint.end());
    for(auto &i : paint){
        int rs = i.second + 1;
        int re = i.second + tsize[rdfn[i.second]];
        int ps = (int)(lower_bound(paint.begin(), paint.end(), pi(i.first,rs)) - paint.begin());
        int pe = (int)(lower_bound(paint.begin(), paint.end(), pi(i.first,re)) - paint.begin());
        dlow[ps]++;
        dlow[pe]--;
        if(i.second != dfn[1]){
            dlow2[ps]++;
            dlow2[pe]--;
        }
    }
    for(int i=1; i<=piv; i++){
        dlow[i] += dlow[i-1];
        dlow2[i] += dlow2[i-1];
    }
    for(int i=0; i<piv; i++){
        if(dlow[i]) low[paint[i].second] = 1;
        if(dlow2[i]) low2[paint[i].second] = 1;
    }
    for(int i=1; i<=piv; i++){
        if(nodev[i] == 0 && low2[dfn[i]]) ret++;
    }
    lint tmp = 0;
    vector<pi> vals;
    for(int i=2; i<=piv;){
        vector<pi> subs;
        for(int j=i; j<i + tsize[rdfn[i]]; j++){
            int pos = rdfn[j];
            subs.push_back(pi(nodev[pos], min(low[j],1)));
            vals.push_back(pi(nodev[pos], min(low[j],1)));
        }
        i += tsize[rdfn[i]];
        tmp -= solve2(subs);
    }
    tmp += solve2(vals);
    ret += tmp;
    for(auto &i : graph[t]){
        if(!vis[i.second]) solve(i.second);
    }
}
 
int main(){ 
    scanf("%d",&n);
    for(int i=0; i<n-1; i++){
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        x = 2 * x - 1;
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
    }
    solve(1);
    printf("%lld",ret);
}