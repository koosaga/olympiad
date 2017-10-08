#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> ti[10005];
int dp[10005][55];

int f(int x, int y){
    if(x == 10001) return 0;
    if(~dp[x][y]) return dp[x][y];
    if(ti[x].empty()) return dp[x][y] = f(x+1, y);
    if(ti[x].size() == 1 && ti[x][0] == y){
        return dp[x][y] = f(x+1, y);
    }
    int ret = 1e9;
    int has = 0;
    for(auto &i : ti[x]){
        if(i == y) has = 1;
    }
    for(auto &i : ti[x]){
        if(i == y){
            ret = min(ret, f(x+1, i) + (int)ti[x].size());
        }
        else{
            ret = min(ret, f(x+1, i) - has + (int)ti[x].size());
        }
    }
    return dp[x][y] = ret;
}

int main(){
    int n, p = 0;
    while(~scanf("%d",&n)){
        memset(dp, -1, sizeof(dp));
        for(int i=0; i<=10000; i++){
            ti[i].clear();
        }
        for(int i=0; i<n; i++){
            int p;
            scanf("%d",&p);
            int pv = -1;
            for(int j=0; j<p; j++){
                int q;
                scanf("%d",&q);
                if(pv == q) continue;
                pv = q;
                ti[q].push_back(i);
            }
        }
        int ret = 1e9;
        for(int i=0; i<n; i++){
            ret = min(ret, f(0, i));
        }
        ret *= 2;
        ret -= n-1;
        printf("Case %d: %d\n", ++p, ret);
    }
}