#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k;
int a[55][55];
int dp[55][55];
vector<pi> v;

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> a[i][j];
			v.emplace_back(i, j);
		}
	}
	sort(all(v), [&](const pi &p, const pi &q){
		return a[p.first][p.second] < a[q.first][q.second];
	});
	int ret = 1e9;
	for(int i=0; i<sz(v); i++){
		int val = a[v[i].first][v[i].second];
		if(val == 1) dp[v[i].first][v[i].second] = 0;
		else{
			int x = v[i].first;
			int y = v[i].second;
			int ret = 1e9;
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					if(a[j][k] == val - 1){
						ret = min(ret, dp[j][k] + 
						abs(j-x) + abs(k-y));
					}
				}
			}
			dp[x][y] = ret;
		}
		if(val == k) ret = min(ret, dp[v[i].first][v[i].second]);
	}
	if(ret > 1e8) ret = -1;
	cout << ret << endl;
}
