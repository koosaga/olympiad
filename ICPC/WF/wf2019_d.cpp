#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;
const int mod = 1e9 + 7;

vector<int> gph[MAXN];
vector<int> tree[MAXN];
vector<pi> soln;
int deg[MAXN], vis[MAXN];

void dfs(int x, int p){
	vis[x] = 1;
	for(auto &y : tree[x]) if(y != p) dfs(y, x);
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<int> a(n);
	vector<vector<pi>> v(1000001);
	for(int i = 0; i < n; i++){
		string s; cin >> s;
		int foo = 0;
		for(int j = 1; j < sz(s); j++) foo = foo * 10 + (s[j] - '0');
		v[foo].emplace_back(i, s[0] == 'e' ? -1 : 1);
	}
	vector<int> dx(n + 1);
	for(int i = 1; i <= 1000000; i++){
		if(sz(v[i]) == 0) continue;
		int sum = 0, minVal = 0;
		for(int j = 0; j < sz(v[i]); j++){
			sum += v[i][j].second;
			minVal = min(minVal, sum);
		}
		if(sum) continue;
		for(int j = 0; j < sz(v[i]); j++){
			sum += v[i][j].second;
			if(minVal == sum){
				int l = v[i][j].first;
				int r = v[i][(j + 1) % sz(v[i])].first;
				if(l < r){
					dx[l+1]++;
					dx[r+1]--;
				}
				else{
					dx[l+1]++;
					dx[n]--;
					dx[0]++;
					dx[r+1]--;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) dx[i] += dx[i - 1];
	int mx = max_element(all(dx)) - dx.begin();
	cout << mx + 1 << " " << dx[mx] << "\n";
}
