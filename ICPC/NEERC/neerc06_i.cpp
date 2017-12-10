#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

map<vector<int>, double> mp;

int n, m, adj[33][33], vis[33];

double f(vector<int> v){
    if(v.size() == 1) return 0;
    if(mp.find(v) != mp.end()) return mp[v];
    int cnt = 0, cmb = n * (n-1) / 2;
    for(auto &i : v){
        cnt += i * (i-1) / 2;
    }
    double ret = 0;
    for(int i=0; i<v.size(); i++){
        for(int j=0; j<i; j++){
            vector<int> w = {v[i] + v[j]};
            for(int k=0; k<v.size(); k++){
                if(k == i || k == j) continue;
                w.push_back(v[k]);
            }
            sort(w.begin(), w.end());
            ret += v[i] * v[j] * f(w);
        }
    }
    ret += cmb;
    ret /= cmb - cnt;
    return mp[v] = ret;
}
int dfs(int x){
    if(vis[x]) return 0;
    vis[x] = 1;
    int ret = 1;
    for(int i=1; i<=n; i++) if(adj[x][i]) ret += dfs(i);
    return ret;
}

int main(){
    cin >> n >> m;
    while(m--){
        int s, e;
        cin >> s >> e;
        adj[s][e] = adj[e][s] = 1;
    }
    vector<int> v;
    for(int i=1; i<=n; i++){
        if(!vis[i]){
            v.push_back(dfs(i));
        }
    }
    sort(v.begin(), v.end());
    printf("%.10f", f(v));
}

