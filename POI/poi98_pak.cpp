#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int n, m;
vector<int> v[1005];
int q[1005];

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		int x, y; cin >> x >> y;
		v[x].push_back(y);
	}
	cin >> m;
	for(int i=0; i<m; i++){
		int x, y; cin >> x >> y;
		q[x] += y;
	}
	int ans = 0;
	for(int i=0; i<=1000; i++){
		sort(v[i].begin(), v[i].end());
		if(q[i] > v[i].size()){
			puts("NIE");
			return 0;
		}
		ans += accumulate(v[i].begin(), v[i].begin() + q[i], 0);
		for(int j=q[i] + 1; j<v[i].size(); j+=2){
			v[i+1].push_back(v[i][j-1] + v[i][j]);
		}
	}
	cout << ans << endl;
}
