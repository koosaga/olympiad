#include <cstdio>
#include <algorithm>
using namespace std;
const int mod = 1e9 + 9;
 
char str[30005];
int n;
int dp[2][15005];
 
int main(){
	scanf("%d %s",&n,str); 
	if(n % 2){
		puts("0");
		return 0;
	}
	dp[0][0] = 1;
	for(int i=n-1; i>=0; i--){
		for(int j=i%2; j<=n-i && j<=i; j+=2){
			if(str[i] == ')'){
				dp[i%2][j] = (j ? dp[(i+1)%2][j-1] : 0);
				continue;
			}
			dp[i%2][j] = dp[(i+1)%2][j+1];
			if(j) dp[i%2][j] += dp[(i+1)%2][j-1];
			dp[i%2][j] %= mod;
		}
	}
	printf("%d",dp[0][0]);
}