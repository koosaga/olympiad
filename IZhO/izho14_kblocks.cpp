#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
 
int dp[105][100005];
int a[100005];
int n,k;
 
int main(){
    scanf("%d %d",&n,&k);
    int maxv = 0;
    memset(dp,0x3f,sizeof(dp));
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        maxv = max(maxv,a[i]);
        dp[1][i] = maxv;
    }
    for (int i=2; i<=k; i++) {
        stack<int> s1,s2;
        for (int j=1; j<=n; j++) {
            int my_dp = dp[i-1][j-1];
            while (!s1.empty() && s1.top() < a[j]) {
                my_dp = min(my_dp,s2.top());
                s1.pop();
                s2.pop();
            }
            if(s1.empty() || my_dp + a[j] < s1.top() + s2.top()){
                s1.push(a[j]);
                s2.push(my_dp);
            }
            if(j >= i) dp[i][j] = s1.top() + s2.top();
        }
    }
    printf("%d",dp[k][n]);
}