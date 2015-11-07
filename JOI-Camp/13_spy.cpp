#include <cstdio>
#include <vector>
using namespace std;

int n,m;
int rj,ri;

vector<int> jg[2005], ig[2005];

int jdf[2005], idf[2005], jsz[2005], isz[2005], jrv[2005], irv[2005];
int jp, ip;

int jdfs(int x){
    jdf[x] = ++jp;
    jrv[jp] = x;
    int ret = 1;
    for (auto &i : jg[x]){
        ret += jdfs(i);
    }
    return jsz[x] = ret;
}

int idfs(int x){
    idf[x] = ++ip;
    irv[ip] = x;
    int ret = 1;
    for (auto &i : ig[x]){
        ret += idfs(i);
    }
    return isz[x] = ret;
}

int dp[2005][2005];

int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        int p,q;
        scanf("%d %d",&p,&q);
        if(p == 0) rj = i;
        else jg[p].push_back(i);
        if(q == 0) ri = i;
        else ig[q].push_back(i);
    }
    jdfs(rj);
    idfs(ri);
    int cnt[2005] = {};
    while (m--) {
        int lj, li;
        scanf("%d %d",&lj,&li);
        dp[idf[li]][jdf[lj]]++;
        dp[idf[li]][jdf[lj]+jsz[lj]]--;
        dp[idf[li]+isz[li]][jdf[lj]]--;
        dp[idf[li]+isz[li]][jdf[lj]+jsz[lj]]++;
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            dp[i][j] += dp[i][j-1];
        }
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            dp[j][i] += dp[j-1][i];
        }
    }
    for (int i=1; i<=n; i++) {
        printf("%d\n",dp[idf[i]][jdf[i]]);
    }
}