#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;
const int mod = 1e9 + 7;


struct disj{
	int pa[MAXN], chk[MAXN];
	void init(int n){
		for(int i=0; i<=n; i++){
			pa[i] = i;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	int toggle(int x){
		return chk[find(x)];
	}
	void update(int x){
		x = find(x);
		chk[x] = 1;
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		chk[p] |= chk[q];
		return 1;
	}
}disj;

struct edg{int s, e, x;}a[MAXN];
int n, m, q, w[MAXN];

int main(){
	scanf("%d %d %d",&m,&n,&q);
	for(int i=0; i<m; i++) scanf("%d",&a[i].x);
	for(int i=0; i<q; i++){
		int lv, rv;
		scanf("%d %d",&lv,&rv);
		lv--;
		if(a[lv].s == 0) a[lv].s = rv;
		else if(a[lv].e == 0) a[lv].e = rv;
	}
	for(int i=0; i<m; i++){
		if(a[i].s == 0) a[i].x = 0;
		if(a[i].e == 0) a[i].e = a[i].s;
	}
	disj.init(n);
	sort(a, a+m, [&](const edg &a, const edg &b){
		return a.x > b.x;
	});
	lint ans = 0;
	for(int i=0; i<m; i++){
		if(disj.find(a[i].s) == disj.find(a[i].e)){
			if(!disj.toggle(a[i].s)){
				ans += a[i].x;
				disj.update(a[i].s);
			}
		}
		else{
			if(disj.toggle(a[i].s) == 0 || disj.toggle(a[i].e) == 0){
				disj.uni(a[i].s, a[i].e);
				ans += a[i].x;
			}
		}
	}
	cout << ans << endl;
}
