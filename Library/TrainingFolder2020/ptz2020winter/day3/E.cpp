#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 500005;

int n, a[MAXN];
int dap[MAXN];
int foo[MAXN];

int getsum(int s, int e){
	s = max(s, 1);
	e = min(e, n + 1);
	if(s <= e) return a[e] - a[s - 1];
	return 0;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		a[x] ^= 1;
	}
	for(int i=1; i<=n+1; i++) a[i] += a[i-1];
	for(int i=1; i<=n; i<<=1){
		for(int j=n; j>=0; j--){
			foo[j] = getsum(j + i, j + 2 * i - 1);
			if(j + 2 * i <= n) foo[j] += foo[j + 2 * i];
		}
		for(int j=i; j<=n+1; j++){
			int block_size = (j - 1) / (2 * i) + 1;
			block_size *= 2 * i;
			int rem = min(block_size - j, i);
			int sum = 0;
			for(int k=0; k<=n; k+=j){
				sum += foo[k];
				if(k + block_size <= n + 1) sum -= foo[k + block_size];
				sum -= getsum(k + block_size - rem, k + block_size - 1);
			}
			if(sum % 2) dap[j] = 1;
		}
	}
	for(int i=2; i<=n+1; i++){
		printf(dap[i] ? "Alice " : "Bob ");
	}
}
