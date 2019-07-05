#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;

void ass(bool p){
	if(!p){
		puts("-1");
		exit(0);
	}
}

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m;
vector<int> gph[MAXN];
vector<int> drz[MAXN];

bool has_edge(int x, int y){
	return binary_search(gph[x].begin(), gph[x].end(), y);
}

void Haja(vector<int> ord, int l, int v1, int v2, vector<int> s1, vector<int> s2){
	swap(ord.back(), *find(ord.begin(), ord.end(), v2));
	swap(ord[ord.size() - 2], *find(ord.begin(), ord.end(), v1));
	vector<int> rev(n + 1);
	for(int i=0; i<ord.size(); i++) rev[ord[i]] = i;
	vector<pi> drog;
	drog.emplace_back(v1, v2);
	for(auto &i : s1) drog.emplace_back(v1, i);
	for(auto &i : s2) drog.emplace_back(v2, i);
	for(int i=l-1; i>=0; i--){
		if(has_edge(ord[i], v1) && has_edge(ord[i], v2)){
			if(has_edge(ord[i], s1[0])) drog.emplace_back(v1, ord[i]);
			else drog.emplace_back(v2, ord[i]);
		}
		else{
			pi rev0(-1e9, 1e9);
			pi rev1(-1e9, 1e9);
			for(auto &j : gph[ord[i]]){
				auto k1 = pi(rev[j], j);
				if(rev0 < k1){
					rev1 = rev0;
					rev0 = k1;
				}
				else if(rev1 < k1){
					rev1 = k1;
				}
			}
			if(rev1.second > n) return;
			drog.emplace_back(rev1.second, ord[i]);
		}
	}
	if(drog.size() != n - 1) return;
	disj.init(n);
	for(int i=1; i<=n; i++) drz[i].clear();
	int cnt = m;
	for(auto &i : drog){
		if(!disj.uni(i.first, i.second)) return;
		if(!(cnt > 0 && has_edge(i.first, i.second))){
			return;
		}
		cnt--;
		drz[i.first].push_back(i.second);
		drz[i.second].push_back(i.first);
	}
	for(int i=1; i<=n; i++){
		for(auto &j : drz[i]){
			for(auto &k : drz[i]){
				if(j == k) break;
				if(!(cnt > 0 && has_edge(j, k))){
					return;
				}
				cnt--;
			}
		}
	}
	if(cnt != 0) return;
	printf("1\n%d\n", n);
	for(auto &i : drog){
		printf("%d %d\n", i.first, i.second);
	}
	exit(0);
}

int cnt[MAXN], idx[MAXN], deg[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	if(m == 1ll * n * (n - 1) / 2){
		printf("1\n%d\n", n);
		for(int i=2; i<=n; i++) printf("%d %d\n", 1, i);
		return 0;
	}
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++) sort(gph[i].begin(), gph[i].end());
	priority_queue<pi> pq;
	for(int i=1; i<=n; i++) pq.emplace(cnt[i], i);
	vector<int> ord;
	while(!pq.empty()){
		int x = pq.top().second, y = pq.top().first;
		pq.pop();
		if(cnt[x] != y || idx[x]) continue;
		ord.push_back(x);
		idx[x] = n + 1 - ord.size();
		for(auto &i : gph[x]){
			if(!idx[i]){
				cnt[i]++;
				pq.emplace(cnt[i], i);
			}
		}
	}
	reverse(ord.begin(), ord.end());
	memset(cnt, 0, sizeof(cnt));
	int mark[MAXN] = {};
	for(int i=1; i<=n; i++){
		deg[i] = gph[i].size();
		cnt[deg[i]]++;
	}
	for(int i=0; i<ord.size(); i++){
		if(cnt[n - 1 - i] >= 2){
			ass(cnt[n - 1 - i] == 2);
			vector<int> cent;
			for(int j=1; j<=n; j++){
				if(mark[j]) continue;
				if(deg[j] == n - 1 - i) cent.push_back(j);
			}
			vector<int> v1, v2;
			for(int j=1; j<=n; j++){
				if(mark[j] || deg[j] == n - 1 - i) continue;
				if(v1.empty() || has_edge(v1[0], j)) v1.push_back(j);
				else v2.push_back(j);
			}
			ass(v1.size() > 0);
			ass(v2.size() > 0);
			Haja(ord, i, cent[0], cent[1], v1, v2);
			Haja(ord, i, cent[1], cent[0], v1, v2);
			ass(0);
		}
		mark[ord[i]] = 1;
		cnt[deg[ord[i]]]--;
		for(auto &j : gph[ord[i]]){
			if(mark[j]) continue;
			cnt[deg[j]]--;
			deg[j]--;
			cnt[deg[j]]++;
		}
	}
	ass(0);
}
