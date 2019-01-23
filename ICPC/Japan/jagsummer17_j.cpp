#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using real_t = double;
const int mod = 1e9 + 7;
const int MAXN = 200005;

int n, m, k, q, a[44];
vector<pi> posSecret;

void get_posSecret(){
    int cursum = k;
    for(int i=1; i<=n; i++) cursum -= a[i];
    for(int j=0; j<=m; j++){
        int ls = j, le = j * (a[1] - 1);
        int rs = cursum - (m - j) * (a[1] - 1);
        int re = cursum - (m - j);
        int s = max(ls, rs);
        int e = min(le, re);
        if(s <= e) posSecret.emplace_back(s, e);
    }
}

int capKnap[44][MAXN];
int imp[44][MAXN];
bitset<MAXN> dp;

int query(int p, int l, int r){
    return imp[p][r] - (l ? imp[p][l-1] : 0);
}

int main(){
    scanf("%d %d %d %d",&n,&m,&k,&q);
    for(int i=1; i<=n; i++) scanf("%d",&a[i]);
    get_posSecret();
    dp[0] = 1;
    for(int i=1; i<=n; i++){
        dp |= (dp << a[i]);
    }
    for(int i=1; i<=n; i++){
        bitset<MAXN> newDp;
        newDp[0] = 1;
        for(int j=1; j<=n; j++){
            if(i != j) newDp |= (newDp << a[j]);
        }
        for(int j=0; j<=k; j++){
            if(dp[j] && !newDp[j]){
                capKnap[i][j] = 1;
            }
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=0; j<=k; j++){
            if(dp[j] && !capKnap[i][j]){
                imp[i][j]++;
            }
            if(j) imp[i][j] += imp[i][j-1];
        }
    }
    while(q--){
        int x; scanf("%d",&x);
        vector<int> ans;
        for(int i=1; i<=n; i++){
            int cnt_should = 1;
            for(auto &j : posSecret){
                int l = x - j.second;
                int r = x - j.first;
                if(r >= 0){
                    l = max(l, 0);
                    if(query(i, l, r)) cnt_should = 0;
                }
            }
            if(cnt_should) ans.push_back(i);
        }
        if(ans.empty()) puts("-1");
        else{
            for(auto &i : ans) printf("%d ", i);
            puts("");
        }
    }
}
