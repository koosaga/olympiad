#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 10005;

int che[MAXN];
int prs[MAXN], cnt, n;

int main(){
	freopen("gcd.in", "r", stdin);
	freopen("gcd.out", "w", stdout);
	fill(che + 2, che + MAXN, 1);
	for(int i=2; i<MAXN; i++){
		for(int j=2*i; j<MAXN; j+=i){
			che[j] = 0;
		}
	}
	cin >> n;
	for(int i=2; i<=n; i++){
		if(che[i]){
			prs[cnt++] = i;
		}
	}
	int dap = 0;
	for(int i=1; i<=cnt/2; i++){
		bool good = 1;
		for(int j=0; j<i; j++){
			if(prs[j] * prs[2*i-1-j] > n) good = 0;
		}
		if(good) dap = i;
	}
	cout << cnt - dap << endl;
}
