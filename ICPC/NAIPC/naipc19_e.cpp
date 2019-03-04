#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi =pair<int,int>;
const int mod = 1e9 + 7;

int n, m;
int a[22][22];
int ord[22][22];
vector<pi> v[1<<20];

int dp[22];

int solve(int pos){
	for(auto &i : v[pos]){
		dp[i.first] = dp[i.second] = 1;
	}
	for(auto &i : v[pos]){
		dp[i.second] += dp[i.first];
	}
	int ret = 0;
	for(auto &i : v[pos]){
		if(dp[i.first]) ret += dp[i.first] - 1;
		dp[i.first] = 0;
		if(dp[i.second]) ret += dp[i.second] - 1;
		dp[i.second] = 0;
	}
	return ret;
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> a[i][j];
		}
	}
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			for(int k=0; k<m; k++){
				if(a[i][k] < a[j][k]) ord[i][j] |= (1<<k);
			}
		}
	}
	lint ret = 0;
	for(int i=1; i<(1<<m); i++){
		vector<int> rw;
		for(int j=0; j<n; j++){
			bool ok = 1;
			int prv = -1e9;
			for(int k=0; k<m; k++){
				if((i >> k) & 1){
					if(prv < a[j][k]) prv = a[j][k];
					else ok = 0; 
				}
			}
			if(ok){
				rw.push_back(j);
				continue;
			}
			ok = 1;
			prv = 1e9;
			for(int k=0; k<m; k++){
				if((i >> k) & 1){
					if(prv > a[j][k]) prv = a[j][k];
					else ok = 0; 
				}
			}
			if(ok){
				rw.push_back(j);
				continue;
			}
		}
		ret += rw.size();
		vector<int> cv;
		for(int j=0; j<rw.size(); j++){
			for(int k=j+1; k<rw.size(); k++){
				int nxt = ord[rw[j]][rw[k]] & i;
				if(v[nxt].empty()) cv.push_back(nxt);
				v[nxt].emplace_back(j, k);
			}
		}
		for(auto &i : cv){
			ret += solve(i);
			v[i].clear();
			v[i].shrink_to_fit();
		}
	}
	cout << ret << endl;
}
