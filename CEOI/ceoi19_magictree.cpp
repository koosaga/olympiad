#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, lint>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

int n, m, p[MAXN];
pi a[MAXN];
vector<int> gph[MAXN];
map<int, lint> mp[MAXN];
int idx[MAXN];

int main(){
	scanf("%d %d %*d",&n,&m);
	for(int i=2; i<=n; i++){
		scanf("%d",&p[i]);
		gph[p[i]].push_back(i);
	}
	for(int i=0; i<m; i++){
		int v, x, y; scanf("%d %d %d",&v,&x,&y);
		a[v] = pi(x, y);
	}
	for(int i=n; i>=1; i--){
		idx[i] = i;
		for(auto &j : gph[i]){
			// it's the dohamsu!
			if(mp[idx[i]].size() < mp[idx[j]].size()){
				swap(idx[i], idx[j]);
			}
			for(auto &k : mp[idx[j]]){
				mp[idx[i]][k.first] += k.second;
			}
		}
		if(a[i].first){
			mp[idx[i]][a[i].first] += a[i].second;
			lint sum = a[i].second;
			auto j = mp[idx[i]].lower_bound(a[i].first + 1);
			while(sum > 0 && j != mp[idx[i]].end()){
				j->second -= sum;
				if(j->second <= 0){
					sum = -(j->second);
					j = mp[idx[i]].erase(j);
				}
				else break;
			}
		}
	}
	lint ret = 0;
	for(auto &i : mp[idx[1]]) ret += i.second;
	cout << ret << endl;
}
