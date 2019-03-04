#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct tup{
	int up, dn, cst;
	bool operator<(const tup &t)const{
		return dn < t.dn;
	}
};

int n, d1[305][45005], d2[305][45005];

vector<tup> v1, v2;

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		int cur = 0, minv = 0;
		for(auto &j : s){
			if(j == '(') cur++;
			else cur--;
			minv = min(minv, cur);
		}
		tup t = {cur - minv, -minv, (int)s.size()};
		if(t.up <= t.dn){
			swap(t.up, t.dn);
			v1.push_back(t);
		}
		else v2.push_back(t);
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	fill(d1[0] + 1, d1[0] + 45005, -1e9);
	fill(d2[0] + 1, d2[0] + 45005, -1e9);
	for(int i=1; i<=v1.size(); i++){
		tup t = v1[i-1];
		for(int j=0; j<45005; j++){
			d1[i][j] = d1[i-1][j];
			if(j >= t.up){
				d1[i][j] = max(d1[i][j], d1[i-1][j + t.dn - t.up] + t.cst);
			}
		}
	}
	for(int i=1; i<=v2.size(); i++){
		tup t = v2[i-1];
		for(int j=0; j<45005; j++){
			d2[i][j] = d2[i-1][j];
			if(j >= t.up){
				d2[i][j] = max(d2[i][j], d2[i-1][j + t.dn - t.up] + t.cst);
			}
		}
	}
	int ans = 0;
	for(int i=0; i<45005; i++){
		ans = max(ans, d1[v1.size()][i] + d2[v2.size()][i]);
	}
	cout << ans;
}
