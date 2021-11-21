#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

vector<int> get(int x1, int y1, int z1, int x2, int y2, int z2){
	vector<int> v = {x1 - x2, y1 - y2, z1 - z2};
	for(auto &i : v) i = abs(i);
	sort(all(v));
	if(v[0] == v[1] || v[1] == v[2]) v[0] = 0;
	return v;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	vector<int> a(3); 
	for(auto &i : a) cin >> i;
	vector<int> p = {0, 1, 2};
	lint ans = 0;
	do{
		for(int i = 1; i <= a[p[0]]; i++){
			int d = min({i - 1, a[p[1]] - i, a[p[2]] - i});
			ans += max(d, 0);
		}
		for(int i = 1; i <= a[p[2]]; i++){
			int d = min({i - 1, a[p[1]] - i, a[p[0]] - i});
			ans += max(d, 0);
		}
	}while(next_permutation(all(p)));
	cout << ans * 4 << endl;
}
