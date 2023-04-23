#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXT = 6005;

int k, n, m;
vector<vector<int>> a;

int Mod(lint x){
    return (x % k + k) % k;
}

int dist[3 * MAXT], par[3 * MAXT];
unordered_map<lint, int> dp, path;

bool dfs(lint N){
    if(abs(N) <= m){
        if(dist[N + MAXT] <= 1e7) return dp[N] = true;
        return dp[N] = false;
    }
    if(dp.count(N)) return dp[N];
    lint modv = Mod(N);
    if(sz(a[modv]) == 0) return dp[N] =false;
    for(auto &x : a[modv]){
        if(dfs((N - x) / k)){
            path[N] = x;
            return dp[N] = true;
        }
    }
    return dp[N] = false;
}

vector<int> w;
void trace(lint N){
    vector<int> v;
    while(N){
        if(abs(N) > m){
            v.push_back(path[N]);
            N -= v.back();
            N /= k;
        }
        else{
            v.push_back(par[N + MAXT]);
            N -= v.back();
            N /= k;
        }
    }
    reverse(all(v));
    w = v;
}


int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin >> k >> q >> n >> m;
    a.resize(k);
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
        a[Mod(v[i])].push_back(v[i]);
    }
    memset(dist, 0x3f, sizeof(dist));
    queue<int> que;
    auto enq = [&](lint x, int d, int p){
        if(abs(x) > MAXT) return;
        if(dist[x + MAXT] > d){
            dist[x + MAXT] = d;
            par[x + MAXT] = p;
            que.push(x);
        }
    };
    enq(0, 0, -1);
    while(sz(que)){
        int x = que.front(); que.pop();
        for(int i = 0; i < n; i++){
            enq(1ll * x * k + v[i], dist[x + MAXT] + 1, v[i]);
        }
    }
    while(q--){
        lint N; cin >> N;
        if(N == 0){
            bool ok = 0;
            for(auto &x : a[0]){
                if(dfs(-x / k)){
                    ok = 1;
                    if(x == 0) w.push_back(0);
                    else{
                        trace(-x / k);
                        w.push_back(x);
                    }
                    for(int i = 0; i < sz(w); i++){
                        cout << w[i];
                        if(i + 1 < sz(w)) cout << " ";
                        else cout <<"\n";
                    }
                    w.clear();
                    break;
                }
            }
            if(!ok) cout << "IMPOSSIBLE\n";
            continue;
        }
        if(dfs(N)){
            trace(N);
            for(int i = 0; i < sz(w); i++){
                cout << w[i];
                if(i + 1 < sz(w)) cout << " ";
                else cout <<"\n";
            }
            w.clear();
        }
        else cout << "IMPOSSIBLE\n";
    }
}
