#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
int num[10005], rev[10005], nxt[10005];
vector<pi> gph[105];

int main(){
	cin >> n;
	int idx = 0;
	for(int i=1; i<=n; i++){
		int x;
		cin >> x;
		gph[i].resize(x);
		for(auto &j : gph[i]){
			cin >> j.first;
			j.second = ++idx;
		}
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			num[j.second] = gph[j.first].size();
			for(auto &k : gph[j.first]){
				if(k.first == i) rev[j.second] = k.second;
			}
		}
	}
	int prv = -1;
	int nidx = -1;
	while(1){
		map<vector<int>, int> mp;
		prv = nidx;
		nidx = 0;
		for(int j=1; j<=n; j++){
			for(int k=0; k<gph[j].size(); k++){
				vector<int> tmp;
				for(int l=1; l<gph[j].size(); l++){
					int idx = (k + l) % gph[j].size();
					tmp.push_back(num[gph[j][idx].second]);
				}
				int idx = rev[gph[j][k].second];
				tmp.push_back(num[idx]);
				if(mp.find(tmp) == mp.end()) mp[tmp] = ++nidx;
				nxt[idx] = mp[tmp];
			}
		}
		memcpy(num, nxt, sizeof(nxt));
		if(prv == nidx) break;
	}
	vector<int> v[105]; 
	bool vis[105] = {};
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]) v[i].push_back(num[j.second]);
		auto tmp = v[i];
		for(auto &j : gph[i]){
			rotate(tmp.begin(), tmp.begin() + 1, tmp.end());
			v[i] = min(v[i], tmp);
		}
	}
	bool ok = 0;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			vector<int> w;
			for(int j=i; j<=n; j++){
				if(v[i] == v[j]){
					w.push_back(j);
					vis[j] = 1;
				}
			}
			if(w.size() > 1){
				for(auto &j : w) printf("%d ", j);
				ok = 1;
				puts("");
			}
		}
	}
	if(!ok) puts("none");
}
