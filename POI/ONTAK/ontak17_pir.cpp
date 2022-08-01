#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

lint mul[1 << 15];
int pcnt[1 << 15];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m; cin >> n >> m;
	for(int i = 0; i < n; i++){
		cin >> mul[1 << i];
		pcnt[1 << i] = 1;
	}
	for(int i = 1; i < (1<<n); i++){
		if(i == (i & -i)) continue;
		mul[i] = lcm(mul[i - (i & -i)],mul[i & -i]);
		pcnt[i] = -pcnt[i - (i & -i)];
	}
	while(m--){
		lint s = 1, e = 1e18;
		lint Q; cin >> Q;
		while(s != e){
			lint m = (s + e) / 2;
			lint ans = 0;
			for(int j = 1; j < (1<<n); j++){
				ans += pcnt[j] * (m / mul[j]);
			}
			if(ans >= Q) e = m;
			else s = m +1;
		}
		cout << s << "\n";
	}
}
