#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using lint = long long;
using pi = pair<lint, lint>;
 
typedef long long ll;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
 
int N;
int A[5010];
ll D[5010][5010];
ll fac[10100];
ll fnv[10100];
 
ll ipow(ll a, ll n) {
	if (!n) return 1;
	ll t = ipow(a,n/2);
	return t*t%MOD*(n%2?a:1)%MOD;
}
 
ll comb(ll n, ll r) {
	if (n<0) return 0;
	if (r<0||r>n) return 0;
	return fac[n]*fnv[r]%MOD*fnv[n-r]%MOD;
}
 
int main(){
	int T;
 
	fac[0] =1;
	const ll M = 10010;
	for (int i=1;i<=M;i++) fac[i] = fac[i-1]*i%MOD;
	fnv[M] = ipow(fac[M],MOD-2);
	for (int i=M-1;i>=0;i--) fnv[i] = fnv[i+1]*(i+1)%MOD;
 
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&N);
		for (int i=0;i<N;i++) scanf("%d",&A[i]);
		if (N==2) {
			if (A[0]==A[1]) puts("0");
			else puts("1");
			continue;
		}
		reverse(A,A+N);
		if (A[0]==A[1]) {
			puts("0");
			continue;
		}
		vector<int> is;
		is.push_back(0);
		for (int i=1;i<N;i++) {
			if (i+1==N||A[i]!=A[i+1]) is.push_back(i);
		}
		for (int i=0;i<N;i++) {
			for (int j=0;j<=i;j++) D[i][j] = 0;
		}
		D[0][0] = 1;
		for (int id=1;id<(int)is.size();id++) {
			int i = is[id];
			int ip = is[id-1];
			for (int j=0;j<=i&&j<=N/2-1;j++) {
				D[i][j] = 0;
				for (int k=0;k<=i-ip&&k<=j&&k<=1;k++) {
						if (j-k==N/2-1) {
							D[i][j] += D[ip][j - k] * comb(2*(j-k)-ip+1,i-ip-k);
						}
						else {
							D[i][j] += D[ip][j - k] * comb(2 * (j - k) - ip, i - ip - k);
						}
				}
				D[i][j] %= MOD;
//				printf("%d, %d: %lld\n",i,j,D[i][j]);
			}
		}
		printf("%lld\n",D[N-1][N/2-1]);
	}
 
	return 0;
}
