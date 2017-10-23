#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 9;

int n;
lint dp[1000005];

int comp;
bool vis[44];

vector<pi> v;

int dfs(int x){
    if(!vis[x]) return 0;
    vis[x] = 0;
    int ret = 1;
    for(int i=0; i<v.size(); i++){
        if(v[i].first == x){
            ret += dfs(v[i].second);
        }
        if(v[i].second == x){
            ret += dfs(v[i].first);
        }
    }
    return ret;
}

lint solve(){
    memset(vis, 0, sizeof(vis));
    for(auto &i : v){
        vis[i.first] = vis[i.second] = 1;
    }
    int ones = 3 * n - count(vis, vis + comp, true);
    int team = n;
    lint ret = 1;
    for(int i=0; i<comp; i++){
        if(vis[i]){
            team--;
            int sz = dfs(i);
            if(sz > 3) return 0;
            if(sz == 2){
                if(ones == 0) return 0;
                ret *= ones;
                ret %= mod;
                ones--;
            }
        }
    }
    if(team < 0) return 0;
    ret *= dp[team];
    ret %= mod;
    return ret;
}

int m, s[22], e[22], x[22];

int main(){
    cin >> n >> m;
    dp[0] = 1;
    for(int i=1; i<=n; i++){
        dp[i] = dp[i-1] * (((3ll * i - 1) * (3ll * i - 2) / 2) % mod) % mod;
    }
    vector<int> bad;
    vector<int> grp;
    for(int i=0; i<m; i++){
        scanf("%d %d %d",&s[i],&e[i],&x[i]);
        grp.push_back(s[i]);
        grp.push_back(e[i]);
        if(x[i] == 1){
            bad.push_back(i);
        }
    }
    sort(grp.begin(), grp.end());
    grp.resize(unique(grp.begin(), grp.end()) - grp.begin());
    for(int i=0; i<m; i++){
        s[i] = lower_bound(grp.begin(), grp.end(), s[i]) - grp.begin();
        e[i] = lower_bound(grp.begin(), grp.end(), e[i]) - grp.begin();
    }
    comp = grp.size();
    lint ret = 0;
    for(int i=0; i<(1<<bad.size()); i++){
        v.clear();
        int cnt = 1;
        for(int i=0; i<m; i++){
            if(x[i] == 0) v.push_back({s[i], e[i]});
        }
        for(int j=0; j<bad.size(); j++){
            if((i >> j) & 1){
                cnt = -cnt;
                v.push_back({s[bad[j]], e[bad[j]]});
            }
        }
        ret += cnt * solve();
    }
    ret %= mod;
    ret += mod;
    ret %= mod;
    cout << ret << endl;
}