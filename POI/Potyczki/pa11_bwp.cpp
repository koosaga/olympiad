#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;

struct intv{ int s, e, x; 
	bool operator<(const intv &i)const{
		return s < i.s;
	}
};

int n, m, k;
vector<intv> v[MAXN];

int query(int x, int y){
	auto l = --upper_bound(v[x].begin(), v[x].end(), (intv){y, 0, 0});
	return l->x;
}

bool solve(){
	if(n == 1) return true;
	for(int i=2; i<=n; i++){
		for(int j=0; j+1<v[i].size(); j++){
			int l = query(i-1, v[i][j].e);
			int r = query(i-1, v[i][j].e + 1);
			if(l + v[i][j+1].x != r + v[i][j].x) return 0;
		}
		for(int j=0; j+1<v[i-1].size(); j++){
			int l = query(i, v[i-1][j].e);
			int r = query(i, v[i-1][j].e + 1);
			if(l + v[i-1][j+1].x != r + v[i-1][j].x) return 0;
		}
	}
	return 1;
}

vector<pi> ev[MAXN];

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		for(int i=0; i<MAXN; i++) v[i].clear(), ev[i].clear();
		scanf("%d %d %d",&n,&m,&k);
		for(int i=0; i<k; i++){
			int a, b, c, p;
			scanf("%d %d %d %d",&a,&b,&c,&p);
			v[a].push_back((intv){b, c, p});
		}
		for(int i=1; i<=n; i++){
			sort(v[i].begin(), v[i].end());
			if(v[i].empty()){
				v[i].push_back((intv){1, m, 0});
				continue;
			}
			vector<intv> tmp;
			if(v[i][0].s > 1) tmp.push_back({1, v[i][0].s - 1, 0});
			if(v[i].back().e < m) tmp.push_back({v[i].back().e + 1, m, 0}); 
			for(int j=1; j<v[i].size(); j++){
				if(v[i][j-1].e + 1 != v[i][j].s){
					intv nxt = {v[i][j-1].e + 1, v[i][j].s - 1, 0};
					tmp.push_back(nxt);
				}
			}
			for(auto &j : tmp) v[i].push_back(j);
			sort(v[i].begin(), v[i].end());
		}
		if(n < m){
			bool ok = 1;
			for(int i=1; i<=n; i++){
				for(int j=1; j<v[i].size(); j++){
					if(v[i][j].x != v[i][j-1].x) ok = 0;
				}
			}
			puts(ok ? "TAK" : "NIE");
		}
		if(n > m){
			multiset<int> s;
			bool ok = 1;
			for(int i=1; i<=n; i++){
				for(auto &j : v[i]){
					ev[j.s].push_back(pi(j.x, 1));
					ev[j.e + 1].push_back(pi(j.x, -1));
				}
			}
			for(int i=1; i<=m; i++){
				for(auto &j : ev[i]){
					if(j.second == -1) s.erase(s.find(j.first));
				}
				for(auto &j : ev[i]){
					if(j.second == 1) s.insert(j.first);
				}
				auto l = *s.rbegin();
				auto r = *s.begin();
				if(l != r) ok = 0;
			}
			puts(ok ? "TAK" : "NIE");
		}
		if(n == m) puts(solve() ? "TAK" : "NIE");
	}
}