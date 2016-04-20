#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
 
int a[150005],n,m;
 
vector<int> l;
int graph[150005][3];
int piv, cnt;
int dp[150005][2];
int low[150005], high[150005];
 
void f(int x){
    if(x <= n){
        if(a[x] >= piv){
            dp[x][0] = 1e7;
            dp[x][1] = 0;
        }
        else if(a[x] != 0){
            dp[x][0] = 0;
            dp[x][1] = 1e7;
        }
        else{
            dp[x][0] = 0;
            dp[x][1] = 1;
        }
        return;
    }
    dp[x][0] = dp[x][1] = 1e7;
    f(graph[x][0]);
    f(graph[x][1]);
    f(graph[x][2]);
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            for (int k=0; k<2; k++) {
                int cost = dp[graph[x][0]][i] + dp[graph[x][1]][j] + dp[graph[x][2]][k];
                if(i + j + k <= 1){
                    dp[x][0] = min(dp[x][0],cost);
                }
                else{
                    dp[x][1] = min(dp[x][1],cost);
                }
            }
        }
    }
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int p,q;
        scanf("%d %d",&p,&q);
        a[q] = p;
    }
    for (int i=0; i<n-m; i++) {
        int r;
        scanf("%d",&r);
        l.push_back(r);
    }
    int pt = n+1;
    for (int i=1; i+2<pt; i+=3) {
        for (int j=i; j<=i+2; j++) {
            graph[pt][j-i] = j;
        }
        pt++;
    }
    pt--;
    sort(l.begin(),l.end());
    int s = 0, e = 1e9;
    while (s != e) {
        piv = (s+e+1)/2;
        cnt = (int)(l.end() - lower_bound(l.begin(),l.end(),piv));
        memset(dp,0,sizeof(dp));
        f(pt);
        if(dp[pt][1] <= cnt) s = piv;
        else e = piv - 1;
    }
    printf("%d",s);
}