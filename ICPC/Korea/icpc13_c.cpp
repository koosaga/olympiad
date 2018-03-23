#include <cstdio>
const int mod = 10007;

int t[50005];
int sum[50005];

void solve(){
	int n;
	scanf("%d",&n);
	printf("%d %d\n",t[n], n * (t[n] + 2 * sum[n-1]) % mod);
}

void tt(){
	t[1] = 1;
	sum[1] = 1;
	for(int i=2; i<=50000; i++){
		t[i] = t[i-1] * 4 - t[i-2];
		t[i] %= mod;
		t[i] += mod;
		t[i] %= mod;
		sum[i] = t[i];
		sum[i] += sum[i-1];
		sum[i] %= mod;
	}
}
int main(){
	tt();
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
}