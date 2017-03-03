#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int h1 = 409, h2 = 433;

int n, indeg[2005], a[2005];

vector<int> gph[2005];

lint dfs(int x){
	vector<lint> v;
	for(auto &i : gph[x]){
		if(!indeg[i]) v.push_back((h1 * dfs(i)) ^ h2);
	}
	sort(v.begin(), v.end());
	if(v.empty()) return 1243;
	lint ret = 0, coeff = 1;
	for(int i=0; i<v.size(); i++){
		ret += coeff * v[i];
		coeff *= h2;
	}
	return ret;
}

vector<lint> solve(){
	memset(indeg, 0, sizeof(indeg));
	for(int i=1; i<=n; i++){
		cin >> a[i];
		gph[a[i]].push_back(i);
		indeg[a[i]]++;
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!indeg[i]) que.push(i);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		indeg[a[x]]--;
		if(indeg[a[x]] == 0) que.push(a[x]);
	}
	vector<lint> ret;
	for(int i=1; i<=n; i++){
		if(indeg[i]){
			vector<lint> t;
			t.push_back(dfs(i));
			for(int j=a[i]; j!=i; j=a[j]){
				t.push_back(dfs(j));
			}
			vector<lint> ans = t;
			for(int i=1; i<t.size(); i++){
				rotate(t.begin(), t.begin() + 1, t.end());
				if(ans > t) ans = t;
			}
			lint hsh = 0, coeff = 1;
			for(int i=0; i<ans.size(); i++){
				hsh += coeff * ans[i];
				coeff *= h2;
			}
			ret.push_back(hsh);
		}
	}
	sort(ret.begin(), ret.end());
	for(int i=0; i<=n; i++) gph[i].clear();
	return ret;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		vector<lint> p1 = solve();
		vector<lint> p2 = solve();
		if(p1 == p2) puts("T");
		else puts("N");
	}
}
