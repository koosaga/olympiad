#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

struct disj{
	int pa[MAXN], sz[MAXN];
	void init(int n){
		for(int i=0; i<=n; i++){
			pa[i] = i;
			sz[i] = 1;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
}disj;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
};

int n, m, k, q;
int chk[MAXN];
vector<edg> e1, e2;

pi trial(int x){
	disj.init(n);
	pi ret(0, 0);
	int p = 0;
	for(auto &i : e2){
		while(p < e1.size() && e1[p].x <= i.x + x){
			if(disj.uni(e1[p].s, e1[p].e)) ret.first += e1[p].x;
			p++;
		}
		if(disj.uni(i.s, i.e)){
			ret.second++;
			ret.first += i.x + x;
		}
	}
	while(p < e1.size()){
		if(disj.uni(e1[p].s, e1[p].e)) ret.first += e1[p].x;
		p++;
	}
	return ret;
}

int main(){
	scanf("%d %d %d %d",&n,&m,&k,&q);
	for(int i=0; i<k; i++){
		int x;
		scanf("%d",&x);
		chk[x] = 1;
	}
	disj.init(n);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		disj.uni(s, e);
		if(chk[s] == chk[e]) e1.push_back({s, e, x});
		else e2.push_back({s, e, x});
	}
	for(int i=2; i<=n; i++){
		if(disj.uni(1, i)){
			puts("-1");
			return 0;
		}
	}
	sort(e1.begin(), e1.end());
	sort(e2.begin(), e2.end());
	int s = -1e6, e = 1e6;
	if(trial(s).second < q || trial(e).second > q){
		puts("-1");
		return 0;
	}
	while(s != e){
		int m = s + (e - s) / 2;
		if(trial(m).second <= q) e = m;
		else s = m+1;
	}
	cout << trial(s).first - 1ll * q * s;
}
