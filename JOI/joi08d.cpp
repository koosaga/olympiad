#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n,m;
int sz[151];
int col[151][11], dang[151][11];
int dp[151][11][80];
int f(int pos, int x, int jumped){
    if(pos == n) return 0;
    if(pos == n-1 && jumped) return 0;
    if(dp[pos][x][jumped]) return dp[pos][x][jumped];
    int res = 1e9;
    for (int i=0; i<sz[pos+1]; i++) {
        res = min(res,f(pos+1,i,jumped)+(dang[pos][x] + dang[pos+1][i])*abs(col[pos][x] - col[pos+1][i]));
    }
    if(jumped > 0){
        for (int i=0; i<sz[pos+2]; i++) {
        res = min(res,f(pos+2,i,jumped-1)+(dang[pos][x]+dang[pos+2][i])*abs(col[pos][x] - col[pos+2][i]));
        }
    }
    return dp[pos][x][jumped]=res;
}

int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%d",&sz[i]);
        for (int j=0; j<sz[i]; j++) {
            scanf("%d %d",&col[i][j],&dang[i][j]);
        }
    }
    int res = 1e9;
    for (int i=0; i<sz[1]; i++) {
        res = min(res,f(1,i,m));
    }
    if(m){
    for (int i=0; i<sz[2]; i++) {
        res = min(res,f(2,i,m-1));
    }
    }
    printf("%d",res);
}