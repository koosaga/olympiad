#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 20;

map<vector<int>, int> mp;

int query(vector<int> v){
	if(mp.find(v) != mp.end()) return mp[v];
	for(auto &i : v) printf("%d ", i);
	cout << endl;
	fflush(stdout);
	int x; cin >> x;
	return mp[v] = x;
}

int main(){
	int n;
	cin >> n;
	srand(0x14004);
	vector<int> v(n);
	iota(v.begin(), v.end(), 1);
	random_shuffle(v.begin(), v.end());
	int cur = -1;
	while((cur = query(v)) < n){
		vector<int> w(n);
		iota(w.begin(), w.end(), 0);
		random_shuffle(w.begin(), w.end());
		bool good = 0;
		for(auto &x : w){
			for(int j=0; j<n; j++){
				if(x == j) continue;
				if(j < x){
					vector<int> ov = v;
					rotate(v.begin() + j, v.begin() + x, v.begin() + x + 1);
					if(query(v) > cur){
						good = 1;
						break;
					}
					v = ov;
				}
				if(j > x){
					vector<int> ov = v;
					rotate(v.begin() + x, v.begin() + x + 1, v.begin() + j + 1);
					if(query(v) > cur){
						good = 1;
						break;
					}
					v = ov;
				}
			}
			if(good) break;
		}
	}
}
