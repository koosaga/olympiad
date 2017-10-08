#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;

int n, m, b, s;
vector<pi> gph[5005], rev[5005];

bool vis[5005];
lint f[5005];
lint dp[5005][5005];

void dnc(lint *p, lint *c, int s, int e, int ps, int pe){
    if(s > e) return;
    int m = (s+e)/2;
    lint minv = 1e18;
    int opt = ps;
    for(int i=ps; i<=pe && i < m; i++){
        if(p[i] + 1ll * (m - i - 1) * (f[m] - f[i]) < minv){
            minv = p[i] + 1ll * (m - i - 1) * (f[m] - f[i]);
            opt = i;
        }
    }
    c[m] = minv;
    dnc(p, c, s, m-1, ps, opt);
    dnc(p, c, m+1, e, opt, pe);
}

int main(){
    cin >> n >> b >> s >> m;
    for(int i=0; i<m; i++){
        int s, e, x;
        scanf("%d %d %d",&s,&e,&x);
        gph[s].push_back({x, e});
        rev[e].push_back({x, s});
    }
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    pq.push(pi(0, b+1));
    while(!pq.empty()){
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        f[t.second] += t.first;
        for(auto &i : gph[t.second]){
            pq.push(pi(i.first + t.first, i.second));
        }
    }
    memset(vis, 0, sizeof(vis));
    pq.push(pi(0, b+1));
    while(!pq.empty()){
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        f[t.second] += t.first;
        for(auto &i : rev[t.second]){
            pq.push(pi(i.first + t.first, i.second));
        }
    }
    sort(f+1, f+b+1);
    for(int i=1; i<=b; i++){
        f[i] += f[i-1];
    }
    memset(dp[0], 0x3f, sizeof(dp[0]));
    dp[0][0] = 0;
    for(int i=1; i<=s; i++){
        memset(dp[i], 0x3f, sizeof(dp[i]));
        dnc(dp[i-1], dp[i], 1, b, 0, b-1);
    }
    cout << dp[s][b];
}