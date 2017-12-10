#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> gph[50005];
int dfn[50005], low[50005], piv1;

vector<int> bcc[50005], cmp[50005];
int piv2;

void dfs1(int x, int p){
    dfn[x] = low[x] = ++piv1;
    for(auto &i : gph[x]){
        if(i == p) continue;
        if(!dfn[i]){
            dfs1(i, x);
            low[x] = min(low[x], low[i]);
        }
        else low[x] = min(low[x], dfn[i]);
    }
}

void dfs2(int x, int c){
    if(c > 0){
        cmp[c].push_back(x);
        bcc[x].push_back(c);
    }
    for(auto &i : gph[x]){
        if(bcc[i].size()) continue;
        if(low[i] >= dfn[x]){
            piv2++;
            cmp[piv2].push_back(x);
            bcc[x].push_back(piv2);
            dfs2(i, piv2);
        }
        else dfs2(i, c);
    }
}

pi solve(int c){
    if(cmp[c].size() == 2){
        vector<pi> v;
        for(auto &j : bcc[cmp[c][1]]){
            if(c == j) continue;
            v.push_back(solve(j));
        }
        sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
            return a.second > b.second;
        });
        int ret = 1, len = 1;
        for(auto &i : v){
            ret = max(ret, i.first);
            ret = max(ret, i.second + 1);
            len = max(len, i.second + 1);
        }
        if(v.size() >= 2) ret = max(ret, v[0].second + v[1].second);
        return pi(ret, len);
    }
    int ret = cmp[c].size() / 2, len = cmp[c].size() / 2;
    vector<pi> v;
    for(int i=1; i<cmp[c].size(); i++){
        int x = cmp[c][i];
        for(auto &j : bcc[x]){
            if(c == j) continue;
            auto l = solve(j);
            len = max(len, l.second + min(i, (int)cmp[c].size() - i));
            ret = max(ret, l.second + (int)cmp[c].size() / 2);
            ret = max(ret, l.first);
            v.push_back(pi(i, l.second));
        }
    }
    priority_queue<pi> pq;
    int tmp = -1e9, p = 0;
    for(int i=0; i<v.size(); i++){
        while(p < i && v[i].first - v[p].first > (int)cmp[c].size() / 2){
            tmp = max(tmp, v[p].first + v[p].second);
            p++;
        }
        ret = max(ret, (int)cmp[c].size() - v[i].first + tmp + v[i].second);
        while(!pq.empty() && pq.top().second < p) pq.pop();
        if(!pq.empty()) ret = max(ret, v[i].first + v[i].second + pq.top().first);
        pq.push(pi(v[i].second - v[i].first, i));
    }
    return pi(ret, len);
}

int n, m, a[1005];

int main(){
    scanf("%d %d",&n,&m);
    while(m--){
        int l;
        scanf("%d",&l);
        for(int j=0; j<l; j++){
            scanf("%d",&a[j]);
        }
        for(int j=1; j<l; j++){
            gph[a[j-1]].push_back(a[j]);
            gph[a[j]].push_back(a[j-1]);
        }
    }
    dfs1(1, 0);
    dfs2(1, 0);
    vector<int> v;
    int ret = 0;
    for(auto &j : bcc[1]){
        auto i = solve(j);
        ret = max(ret, i.first);
        v.push_back(i.second);
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    if(v.size() >= 2) ret = max(ret, v[0] + v[1]);
    cout << ret;
}
