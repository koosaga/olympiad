#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 5005;

int m, n, r, a[MAXN];
vector<pi> ans;
int prv[MAXN], nxt[MAXN];

void FUCK(){
	puts("-1");
	exit(0);
}

int main(){
	cin >> m >> n >> r;
	vector<pi> b(m);
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=1; i<=n; i++){
		prv[i] = lower_bound(a + 1, a + n + 1, a[i] - r) - a;
		nxt[i] = upper_bound(a + 1, a + n + 1, a[i] + r) - a - 1;
	}
	for(int i=0; i<m; i++) cin >> b[i].first;
	for(int i=0; i<m; i++) cin >> b[i].second;
	auto mode = [&](pi x){ return x.first <= x.second; };
	for(int i=0; i<m; ){
		int e = i;
		while(e < m && mode(b[i]) == mode(b[e])) e++;
		if(mode(b[i]) == 1){
			for(int j=e-1; j>=i; j--){
				int x = b[j].first, y = b[j].second;
				while(nxt[x] < y){
					if(nxt[x] == x) FUCK();
					ans.emplace_back(x, nxt[x]);
					x = nxt[x];
				}
				if(a[y] - a[x] <= r){
					if(x != y) ans.emplace_back(x, y);
				}
				else FUCK();
			}
		}
		else{
			for(int j=i; j<e; j++){	
				int x = b[j].first, y = b[j].second;
				while(prv[x] > y){
					if(prv[x] == x) FUCK();
					ans.emplace_back(x, prv[x]);
					x = prv[x];
				}
				if(a[x] - a[y] <= r){
					if(x != y) ans.emplace_back(x, y);
				}
				else FUCK();
			}
		}
		i = e;
	}
	printf("%d\n", sz(ans));
	for(auto [x, y] : ans) printf("%d %d\n", x, y);
}
