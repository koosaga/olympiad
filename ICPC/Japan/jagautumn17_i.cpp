#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 505;
const int MAXT = 1050000;
const int mod = 1e9 + 7;

int n, m;
bitset<MAXN> gph[MAXN];

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int s, e;
		cin >> s >> e;
		s--, e--;
		gph[s].set(e);
	}
	bitset<MAXN> ans;
	ans.set(0);
	for(int i=0; i<500000; i++){
		bitset<MAXN> nxt;
		for(int j=0; j<n; j++){
			if(ans[j]) nxt |= gph[j];
		}
		ans = nxt;
		if(ans.count() == n){
			cout << i + 1 << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}

