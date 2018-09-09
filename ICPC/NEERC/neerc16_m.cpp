#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, m, up[MAXN], a[MAXN];
pi dp[MAXN];

void update(int v){
    dp[v] = pi(0, v);
    if(a[v] == 0) dp[v].first = 1e9;
    for(auto &i : {2*v, 2*v+1}){
        if(i <= n){
            auto nxt = dp[i];
            if(up[i] > 0) nxt.first--;
            else nxt.first++;
            dp[v] = min(dp[v], nxt);
        }
    }
}

int query(int v){
    auto sol = dp[v];
    int cur_dist = 0;
    for(int i=v; i!=1; i>>=1){
        if(up[i] < 0) cur_dist--;
        else cur_dist++;
        if(a[i / 2] != 0) sol = min(sol, pi(cur_dist, i / 2));
        if((i ^ 1) <= n){
            auto tmp = dp[i ^ 1];
            if(up[i ^ 1] > 0) tmp.first--; 
            else tmp.first++;
            tmp.first += cur_dist;
            sol = min(sol, tmp);
        }
    }
    a[sol.second]--;
    update(sol.second);
    update(v);
    for(int i=v; i!=1; i=i/2){
        up[i]++;
        update(i / 2);
    }
    for(int i=sol.second; i!=1; i=i/2){
        up[i]--;
        update(i / 2);
    }
    return sol.first;
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=n; i; i--) update(i);
    int ans = 0;
    for(int i=1; i<=m; i++){
        int x; scanf("%d",&x);
        ans += query(x);
        printf("%d ", ans);
    }
}

