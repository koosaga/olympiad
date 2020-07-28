// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc17c1p4
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 5010;
ll dp[MAXN],temp[MAXN][2],n,h;
int main(){
	scanf("%lld %lld",&n,&h);
	while(n--){
		ll gi,hi,qi,ti;
		scanf("%lld %lld %lld %lld",&gi,&hi,&qi,&ti);
		for(ll i = 0;i<=h;i++) temp[i][0] = dp[i];
		for(ll i = h;i >= hi;i--){
			temp[i][0] = max(temp[i - hi][0] + gi,temp[i][0]);
		}
		for(ll i = hi;i<=h;i++) temp[i][1] = dp[i - hi];
		for(ll i = hi + ti;i<=h;i++){
			temp[i][1] = max(temp[i][1], temp[i - ti][1] + qi);
		}
		for(ll i = hi;i<=h;i++) temp[i][1] += gi;
		for(ll i = 0;i<=h;i++) dp[i] = max(temp[i][0],temp[i][1]);
	}
	printf("%lld\n",dp[h]);
	return 0;
}