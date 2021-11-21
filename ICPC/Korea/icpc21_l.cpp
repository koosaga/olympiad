#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 2005;

int cnt[11][11][11][11];

int dfs(string &s, string &t, int d, int* idx){
	if(d == 4){
		return cnt[idx[0]][idx[1]][idx[2]][idx[3]];
	}
	if(s[d] == t[d]){
		idx[d] = s[d] - '0';
		return dfs(s, t, d + 1, idx);
	}
	idx[d] = 10;
	int ret = dfs(s, t, d + 1, idx);
	idx[d] = s[d] - '0';
	ret -= dfs(s, t, d + 1, idx);
	idx[d] = t[d] - '0';
	ret -= dfs(s, t, d + 1, idx);
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<string> a(n);
	for(auto &i : a) cin >> i;
	int ret = 0;
	for(int i = 1; i < n; i++){
		for(int x = 0; x < 16; x++){
			int idx[4];
			for(int y = 0; y < 4; y++){
				idx[y] = ((x >> y) % 2 ? 10 : (a[i-1][y] - '0'));
			}
			cnt[idx[0]][idx[1]][idx[2]][idx[3]]++;
		}
		for(int j = i + 1; j < n; j++){
			int idx[4];
			ret += dfs(a[i], a[j], 0, idx);
		}
	}
	cout << ret << endl;
}

