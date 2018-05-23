#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int n,m,r,s,a[20][20];
int b[20][20], cst[20][20], dp[20][20];
 
int solve(int bit){
    memset(b,0,sizeof(b));
    int piv = 0;
    for (int i=0; i<n; i++) {
        for (int j=1; j<=m; j++) {
            b[piv][j] += a[i][j];
        }
        if((bit >> i)&1) piv++;
    }
    for (int i=0; i<=piv; i++) {
        for (int j=1; j<=m; j++) {
            b[i][j] += b[i][j-1];
        }
    }
    for (int i=1; i<=m; i++) {
        for (int j=i; j<=m; j++) {
            int ret = 0;
            for (int k=0; k<=piv; k++) {
                ret = max(ret,b[k][j] - b[k][i-1]);
            }
            cst[i][j] = ret;
        }
    }
    for (int i=1; i<=m; i++) {
        for (int j=0; j<=s; j++) {
            dp[i][j] = cst[1][i];
            if(j != 0){
                for (int k=0; k<i; k++) {
                    dp[i][j] = min(dp[i][j],max(dp[k][j-1],cst[k+1][i]));
                }
            }
        }
    }
    return dp[m][s];
}
 
int main(){
    scanf("%d %d %d %d",&n,&m,&r,&s);
    for (int i=0; i<n; i++) {
        for (int j=1; j<=m; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    int ret = 1e9;
    for (int i=0; i<(1<<(n-1)); i++) {
        int c = 0;
        for (int j=0; j<n-1; j++) {
            if((i>>j)&1) c++;
        }
        if(c == r){
            ret = min(ret,solve(i));
        }
    }
    printf("%d",ret);
}