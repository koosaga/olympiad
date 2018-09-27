#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 105;
const int MAXE = 10005;

struct disj{
	bitset<MAXN> msk[MAXN];
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
		pa[q] = p;
		msk[p] |= msk[q];
		return 1;
	}
}disj;

int n, E;
vector<pi> gph[MAXN];
vector<pi> intime[MAXN];
int s[MAXE], e[MAXE], x[MAXE], nxt[MAXE], vis[MAXE];

struct visit{
	int a, b; // ax + b
	int num;
};

vector<visit> vtx_visit[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int sz; scanf("%d",&sz);
		gph[i].resize(sz);
		for(auto &j : gph[i]){
			s[E] = i;
			scanf("%d %d",&e[E],&x[E]);
			j = pi(e[E], E);
			E++;
		}
	}
	for(int i=0; i<E; i++){
		for(int j=0; j<gph[e[i]].size(); j++){
			if(gph[e[i]][j].first == s[i]){
				auto nxtE = gph[e[i]][(j + gph[e[i]].size() - 1) % gph[e[i]].size()];
				nxt[i] = nxtE.second;
			}
		}
	}
	int k, l;
	scanf("%d %d",&k,&l);
	disj.init(k);
	for(int i=1; i<=k; i++){
		int pos, nxt, sz; 
		scanf("%d %d %d",&pos,&nxt,&sz);
		for(int j=0; j<sz; j++){
			int v; scanf("%d",&v);
			disj.msk[i][v] = 1;
		}
		int start = -1;
		for(auto &j : gph[pos]){
			if(j.first == nxt) start = j.second;
		}
		memset(vis, 0, sizeof(vis));
		int len = 0;
		vector<int> eseq;
		while(!vis[start]){
			len += x[start];
			eseq.push_back(start);
			vis[start] = 1;
			start = ::nxt[start];
		}
		int clen = 0;
		for(auto &j : eseq){
			vtx_visit[s[j]].push_back({len, clen, i});
			clen += x[j];
		}
	}
	for(int i=1; i<=n; i++){
		sort(vtx_visit[i].begin(), vtx_visit[i].end(), [&](const visit &a, const visit &b){
			return a.a < b.a;
		});
		// |vtx_visit[i]| <= 10000
		// distinct number of period = 100 for each i
		vector<pi> intervals;
		for(int j=0; j<vtx_visit[i].size(); ){
			int e = j;
			while(e < vtx_visit[i].size() && vtx_visit[i][j].a == vtx_visit[i][e].a) e++;
			intervals.push_back(pi(j, e));
			j = e;
		}
		for(auto &j : intervals){
			for(auto &k : intervals){
				int l = gcd(vtx_visit[i][j.first].a, vtx_visit[i][k.first].a);
				vector<pi> v;
				for(int p=j.first; p<j.second; p++){
					v.push_back(pi(vtx_visit[i][p].b % l, vtx_visit[i][p].num));
				}
				for(int p=k.first; p<k.second; p++){
					v.push_back(pi(vtx_visit[i][p].b % l, vtx_visit[i][p].num));
				}
				sort(v.begin(), v.end());
				for(int i=1; i<v.size(); i++){
					if(v[i-1].first == v[i].first) disj.uni(v[i-1].second, v[i].second);
				}
				if(j == k) break;
			}
		}
	}
	vector<int> v;
	for(int i=1; i<=k; i++){
		if(disj.msk[disj.find(i)].count() == l) v.push_back(i);
	}
	cout << v.size() << endl;
	for(auto &i : v) cout << i << endl;
}
