#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 1000005;

int n;
char str[1000005];
double dp[MAXN];
double sum[MAXN];
lint ps[2][MAXN];

int main(){
    freopen("foreign.in", "r", stdin);
    freopen("foreign.out", "w", stdout);
    scanf("%s", str);
    n = strlen(str);
    for(int i=n-1; i>=0; i--){
        ps[0][i] = ps[0][i+1] + (n - i) * (str[i] == 'W');
        ps[1][i] = ps[1][i+1] + (n - i) * (str[i] == 'C');
        dp[i] = sum[i + 1] + ps[str[i] == 'W'][i];
        dp[i] /= n - i;
        sum[i] = sum[i + 1] + dp[i];
    }
    printf("%.10f\n", dp[0]);
}
