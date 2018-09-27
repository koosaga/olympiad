#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 3305;

int n, m, s, l[MAXN], r[MAXN];
bitset<101> msk[MAXN];
bool vis[MAXN];

bitset<101> dfs(int x){
	if(x <= n || vis[x]) return msk[x];
	vis[x] = 1;
	return msk[x] = (dfs(l[x]) ^ dfs(r[x])); 
}

int main(){
	cin >> n >> m >> s;
	for(int i=1; i<=n; i++){
		msk[i].set(i - 1);
	}
	for(int i=n+1; i<=n+m; i++){
		cin >> l[i] >> r[i];
		if(l[i] < 0) l[i] = -l[i];
		else l[i] += n;
		if(r[i] < 0) r[i] = -r[i];
		else r[i] += n;
	}
	auto k = dfs(s + n);
	string x, y; cin >> x >> y;
	reverse(x.begin(), x.end());
	reverse(y.begin(), y.end());
	int cnt = 0;
	while(true){
		int res = 0;
		for(int i=0; i<n; i++){
			if(x[i] == '1' && k[n-1-i]){
				res ^= 1;
			}
		}
		if(res) cnt++;
		if(x == y) break;
		x[0]++;
		for(int i=0; i<n; i++){
			if(x[i] == '2'){
				x[i] = '0';
				x[i+1]++;
			}
		}
	}
	cout << cnt << endl;
}
