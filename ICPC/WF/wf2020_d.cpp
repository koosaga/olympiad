#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;


const int MAXN = 4000005;
char str[MAXN];
int aux[2 * MAXN - 1], ret[2 * MAXN - 1];

void solve(int n, char *str, int *ret){
	// *ret : number of nonobvious palindromic character pair
	for(int i=0; i<n; i++){
		aux[2*i] = str[i];
		if(i != n-1) aux[2*i+1] = -1;
	}
	int p = 0, c = 0;
	for(int i=0; i<2*n-1; i++){
		int cur = 0;
		if(i <= p) cur = min(ret[2 * c - i], p - i);
		while(i - cur - 1 >= 0 && i + cur + 1 < 2*n-1 && aux[i-cur-1] == aux[i+cur+1]){
			cur++;
		}
		ret[i] = cur;
		if(i + ret[i] > p){
			p = i + ret[i];
			c = i;
		}
	}
}

int L[MAXN], R[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> str;
	int n = strlen(str);
	solve(n, str, ret);
	L[0] = 1;
	int idx = 0;
	for(int i = 1; i < n; i++){
		int len = (ret[2 * i - 1] + 1) / 2;
		if(idx >= i - len) L[i] = 1;
		if(L[i]) idx = i;
	}
	R[n] = 1; idx = n;
	for(int i = n - 1; i > 0; i--){
		int len = (ret[2 * i - 1] + 1) / 2;
		if(idx <= i + len) R[i] = 1;
		if(R[i]) idx = i;
	}
	int pos = 0, ans = 1e9;
	for(int i = 0; i < n; i++){
		if(L[i]) pos = i;
		if(R[i + 1]) ans = min(ans, i + 1 - pos);
	}
	cout << ans << "\n";
}
