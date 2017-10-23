#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 4005;

int n, p[4005], mod;
lint a[4005];

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		scanf("%d %d",&n,&mod);
		memset(a, 0, sizeof(a));
		a[0] = 1;
		for(int i=0; i<n; i++) scanf("%d",&p[i]);
		int f0 = 1, f1 = 2;
		for(int i=1; i<=n; i++){
			for(int j=i; j>=0; j--){
				a[j] = (j ? a[j-1] : 0) + mod - a[j] * f0 % mod;
				a[j] %= mod;
			}
			tie(f0, f1) = pi(f1, (f0 + f1) % mod);
		}
		lint ret = 0;
		for(int i=0; i<n; i++){
			ret += a[i] * p[i] % mod;
			ret %= mod;
		}
		cout << (mod - ret) % mod << endl;
	}
}
