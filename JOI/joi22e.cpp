#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const int inf = 20000000;

int solve(vector<int> v){
	int m = sz(v);
	int cnt = 0;
	for(int i = 0; i < 2; i++){
		int j = 0;
		for(int i = 0; i < m; i++){
			j = max(j, i);
			while(j+1 < m && v[j+1] > v[j]) j++;
			cnt += j - i + 1;
		}
		reverse(all(v));
	}
	return cnt - m;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> a(n, vector<int>(m));
	for(auto &i : a) for(auto &j : i) cin >> j;
	if(n > m){
		vector<vector<int>> b(m, vector<int>(n));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++) b[j][i] = a[i][j];
		}
		swap(n, m);
		a = b;
	}
	lint ret = 0;
	for(int i = 0; i < n; i++){
		ret += solve(a[i]);
	}
	for(int i = 0; i < m; i++){
		vector<int> b;
		for(int j = 0; j < n; j++) b.push_back(a[j][i]);
		ret += solve(b);
	}
	ret -= n * m;
	vector<vector<vector<lint>>> sum(16, vector<vector<lint>>(n + 1, vector<lint>(m)));
	for(int b = 1; b < 16; b++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				bool hasHigh = 0;
				int maxOfLow = 0;
				for(int k = 0; k < 4; k++){
					if(b & (1 << k)){
						if(i + dx[k] < 0 || i + dx[k] >= n || j + dy[k] < 0 || j + dy[k] >= m) continue;
						int val = a[i + dx[k]][j + dy[k]];
						if(val < a[i][j]){
							maxOfLow = max(maxOfLow, val);
						}
						else hasHigh = 1;
					}
				}
				sum[b][i+1][j] = sum[b][i][j] + (hasHigh ? a[i][j] : inf) - maxOfLow;
			}
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			vector<lint> val(m);
			vector<lint> start(m), end(m);
			for(int k = 0; k < m; k++){
				val[k] = sum[14][j+1][k] - sum[14][j][k] + sum[15][j][k] - sum[15][i+1][k] + sum[11][i+1][k] - sum[11][i][k];
				start[k] = sum[6][j+1][k] - sum[6][j][k] + sum[7][j][k] - sum[7][i+1][k] + sum[3][i+1][k] - sum[3][i][k];
				end[k] = sum[12][j+1][k] - sum[12][j][k] + sum[13][j][k] - sum[13][i+1][k] + sum[9][i+1][k] - sum[9][i][k];
				if(k) val[k] += val[k - 1];
			}
			map<lint, int> cnt;
			for(int s = 1; s < m; s++){
				cnt[val[s - 1] - start[s - 1] + inf]++;
				ret += cnt[end[s] + val[s - 1]];
			}
		}
	}
	cout << ret << endl;
}
