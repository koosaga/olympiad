#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 200005;
typedef long long lint;
typedef pair<int, int> pi;

set<vector<int>> ncnd;

set<vector<int>> vis;

void split(vector<int> x, vector<int> l, int s, int pos = 0){
	sort(all(l));
	if(vis.find(l) != vis.end()) return;
	vis.insert(l);
	if(pos == sz(x)){
		if(s & 1) ncnd.insert(l);
		return;
	}
	for(int i=0; i<=s&&i<=x[pos]/2; i++){
		if(i) l.push_back(i);
		if(i!=x[pos]) l.push_back(x[pos]-i);
		split(x, l, (s >> (x[pos] - i)) | (s >> i), pos + 1);
		if(i!=x[pos]) l.pop_back();
		if(i) l.pop_back();
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	set<vector<int>> cnd;
	cnd.insert({n});
	for(int i=0; i<m; i++){
		int x; cin >> x;
		vector<int> l;
		for(auto &j : cnd){
			vis.clear();
			split(j, l, 1 << x);
		}
		cnd = ncnd;
		ncnd.clear();
		bool good = 1;
		for(auto &i : cnd){
			if(sz(i) == n){
				good = 0;
				break;
			}
		}
		if(good == 0) break;
	}
	int ret = 0;
	for(auto &i : cnd){
		int dap = 0;
		for(auto &j : i){
			if(j == 1) dap++;
		}
		ret = max(ret, dap);
	}
	cout << ret << endl;
}
