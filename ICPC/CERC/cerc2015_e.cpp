#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;
const int mod = 1e9 + 7;

int deg[300005];
int totv, tote;

struct comp{
	map<int, int> cnt;
	int vcnt, dcnt;
	void invalidate(){
		if(vcnt == 0) return;
		if(vcnt == cnt[2]){
			totv -= 1;
			tote -= 1;
		}
		else{
			totv -= vcnt - cnt[2];
			tote -= dcnt / 2 - cnt[2];
		}
	}
	void validate(){
		if(vcnt == 0) return;
		if(vcnt == cnt[2]){
			totv += 1;
			tote += 1;
		}
		else{
			totv += vcnt - cnt[2];
			tote += dcnt / 2 - cnt[2];
		}
	}
	void merge(comp &c){
		invalidate();
		c.invalidate();
		if(c.cnt.size() > cnt.size()) swap(c.cnt, cnt);
		vcnt += c.vcnt;
		dcnt += c.dcnt;
		for(auto &i : c.cnt){
			cnt[i.first] += i.second;
		}
		validate();
	}
	void update(int x){
		invalidate();
		dcnt++;
		if(x != 0){
			vcnt--;
			cnt[x]--;
		}
		vcnt++;
		cnt[x+1]++;
		validate();
	}
};

struct disj{
	int pa[300005];
	comp c[300005];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	void uni(int p, int q){
		int fp = find(p);
		int fq = find(q);
		if(fp != fq){
			pa[fq] = fp;
			c[fp].merge(c[fq]);
		}
		c[fp].update(deg[p]);
		c[fp].update(deg[q]);
		deg[p]++;
		deg[q]++;
	}
}disj;

struct edg{
	int s, e, x;
};

int n, m, q;
vector<edg> ve;
vector<pi> vq;
int retv[300005], rete[300005];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		ve.push_back({s, e, x});
	}
	disj.init(n);
	sort(ve.begin(), ve.end(), [&](const edg &a, const edg &b){
		return a.x > b.x;
	});
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int p;
		scanf("%d",&p);
		vq.push_back({p, i});
	}
	sort(vq.begin(), vq.end());
	reverse(vq.begin(), vq.end());
	int p = 0;
	for(auto &i : vq){
		while(p < ve.size() && ve[p].x >= i.first){
			disj.uni(ve[p].s, ve[p].e);
			p++;
		}
		retv[i.second] = totv;
		rete[i.second] = tote;
	}
	for(int i=0; i<q; i++){
		printf("%d %d\n", retv[i], rete[i]);
	}
}
