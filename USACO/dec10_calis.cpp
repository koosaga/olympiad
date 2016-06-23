#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, s;
int cnt = 0;
vector<int> gph[100005];
 
int solve(int x, int p, int s){
	vector<int> v;
	for(auto &i : gph[x]){
		if(i == p) continue;
		v.push_back(solve(i, x, s) + 1);
	}
	sort(v.begin(), v.end());
	while(v.size() >= 2 && v[v.size()-2] + v.back() > s){
		cnt++;
		v.pop_back();
	}
	if(v.size() && v.back() > s){
		cnt++;
		v.pop_back();
	}
	if(v.empty()) return 0;
	return v.back();
}
 
int main(){
	cin >> n >> s;
	for(int i=0; i<n-1; i++){
		int s, e;
		cin >> s >> e;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int st = 0, ed = n;
	while(st != ed){
		int m = (st + ed) / 2;
		cnt = 0;
		solve(1, 0, m);
		if(cnt <= s) ed = m;
		else st = m+1;
	}
	cout << st;
}