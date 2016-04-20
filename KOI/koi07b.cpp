#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
const int mod = 20070713;
 
int n;
pi a[100005];
int dp[100005], low[100005];
 
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&a[i].first,&a[i].second);
    }
    sort(a+1,a+n+1);
    for (int i=1; i<=n; i++) {
        low[i] = (int)(lower_bound(a+1,a+n+1,pi(a[i].second+1,0)) - a);
    }
    dp[n+1] = 1;
    for (int i=n; i>=0; i--) {
        dp[i] = dp[i+1] + dp[low[i]];
        dp[i] %= mod;
    }
    printf("%d",dp[0]);
}