#include <cstdio>
#include <algorithm>
using namespace std;
 
int a[305], n, m;
 
int dp1[2][305][305];
int dp2[2][305][305];
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    sort(a,a+n+1);
    int p = (int)(lower_bound(a,a+n+1,0) - a);
    int ret = 0;
    for(int i=1; i<=n; i++){
        for(int j=0; j<=n; j++){
            for(int k=j; k<=n; k++){
                dp1[i%2][j][k] = dp2[i%2][j][k] = 1e9;
                if(j != 0) dp1[i%2][j][k] = min(dp1[i%2][j][k], dp1[(i-1)%2][j-1][k] + i * (a[j] - a[j-1]));
                if(k != n) dp1[i%2][j][k] = min(dp1[i%2][j][k], dp2[(i-1)%2][j][k+1] + i * (a[k+1] - a[j]));
                if(j != 0) dp2[i%2][j][k] = min(dp2[i%2][j][k], dp1[(i-1)%2][j-1][k] + i * (a[k] - a[j-1]));
                if(k != n) dp2[i%2][j][k] = min(dp2[i%2][j][k], dp2[(i-1)%2][j][k+1] + i * (a[k+1] - a[k]));
            }
        }
        ret = max(ret,i * m - dp1[i%2][p][p]);
    }
    printf("%d",ret);
}