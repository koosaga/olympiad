#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 1600005;

struct edge{
    int s, e;
    lint r, p;
    int idx;
    bool operator<(const edge &e)const{
        return r < e.r;
    }
};

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> outdeg(n);
    vector<vector<int>> gph(n);
    vector<edge> edgeVal;
    priority_queue<edge> pq;
    for(int i = 0; i < m; i++){
        int s, e, x, y;
        cin >> s >> e >> x >> y;
        s--; e--;
        edgeVal.push_back({s, e, x, y, i});
        pq.push(edgeVal.back());
        gph[e].push_back(sz(edgeVal) - 1);
        outdeg[s]++;
    }
    for(int i = 0; i < n; i++){
        if(outdeg[i] == 0){
            int w = sz(edgeVal);
            edgeVal.push_back({i, i, (lint)1e18, 0, w});
            gph[i].push_back(sz(edgeVal) - 1);
            pq.push(edgeVal.back());
            outdeg[i]++;
        }
    }
    vector<lint> ans(n, 1e18);
    vector<int> used(sz(edgeVal));
    while(sz(pq)){
        auto x = pq.top();
        pq.pop();
        if(used[x.idx]) continue;
        used[x.idx] = 1;
        outdeg[x.s]--;
        if(outdeg[x.s] == 0){
            ans[x.s] = x.r;
            for(auto &y : gph[x.s]){
                if(!used[y] && edgeVal[y].r < ans[x.s] - edgeVal[y].p){
                    edgeVal[y].r = ans[x.s] - edgeVal[y].p;
                    pq.push(edgeVal[y]);
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(ans[i] > 1e17) ans[i] = -1;
        cout << ans[i] << " ";
    }
}
