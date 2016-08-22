#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
vector<int> gph[5005];

int dcnt[5005];

int dfs(int x, int p, int d){
	dcnt[d]++;
	int ret = d;
	for(auto &i : gph[x]){
		if(i != p){
			ret = max(ret, dfs(i, x, d+1));
		}
	}
	return ret;
}

lint solve(vector<int> &v){
	int pref = 0, suff = 0;
	for(int i=0; i<v.size(); i++){
		suff += v[i];
	}
	lint ret = 0;
	for(auto &i : v){
		suff -= i;
		ret += 1ll * i * pref * suff;
		pref += i;
	}
	return ret;
}

vector<int> v[5005];

int main(){
	cin >> n;
	for(int i=1; i<n; i++){
		int s, e;
		cin >> s >> e;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	lint ret = 0;
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			int len = dfs(j, i, 1);
			for(int k=1; k<=len; k++){
				v[k].push_back(dcnt[k]);
				dcnt[k] = 0;
			}
		}
		for(int j=1; j<=n; j++){
			ret += solve(v[j]);
			v[j].clear();
		}
	}
	cout << ret;
}