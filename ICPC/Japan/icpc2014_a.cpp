#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> v, vector<int> w){
	if(count(v.begin(), v.end(), 1) != count(w.begin(), w.end(), 1)) return 1e9;
	vector<int> p1, p2;
	for(int i=0; i<2; i++){
		for(int j=0; j<v.size(); j++){
			if(v[j] == i){
				int l = p1.size(); p1.push_back(j);
			}
			if(w[j] == i){
				int l = p2.size(); p2.push_back(j);
			}
		}
	}
	int n = v.size();
	int ans = 0;
	vector<int> perm(n);
	for(int i=0; i<v.size(); i++){
		perm[p1[i]] = p2[i];
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(perm[i] < perm[j]) ans++;
		}
	}
	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<int> v, w;
	for(int i=0; i<n; i++){
		int x; cin >> x;
		v.push_back(x);
	}
	for(int i=0; i<m; i++){
		int x; cin >> x;
		for(int j=0; j<x; j++) w.push_back(i % 2);
	}
	int ans = solve(v, w);
	for(auto &i : w) i ^= 1;
	ans = min(ans, solve(v, w));
	cout << ans << endl;
}