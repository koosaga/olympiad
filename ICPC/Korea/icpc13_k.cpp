#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[2][100005];
int a[2][100005];
int n;

int f(int x, int y){
    if(y >= n) return 0;
    if(~dp[x][y]) return dp[x][y];
    return dp[x][y] = a[x][y] + max(f(1-x,y+1),f(1-x,y+2));
}

void calc(){
    scanf("%d",&n);
    for (int i=0; i<2; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    memset(dp,-1,sizeof(dp));
    printf("%d\n",max(f(0,0),f(1,0)));
}
int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        calc();
    }
}

