#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXL = 1000;

int n, k, a[100005];

struct node{
	node *l, *r;
	int cnt, sum;
	node(){
		l = r = NULL;
		cnt = sum = 0;
	}
}*l[100005], *r[100005];

void init(node *p, int s, int e){
	if(s == e) return;
	p->l = new node();
	p->r = new node();
	int m = s + (e-s)/2;
	init(p->l, s, m);
	init(p->r, m+1, e);
}

void add(int pos, int s, int e, node *prv, node *cur){
	cur->sum = prv->sum + pos;
	cur->cnt = prv->cnt + 1;
	if(s == e) return;
	int m = s + (e-s)/2;
	if(pos <= m){
		cur->r = prv->r;
		cur->l = new node();
		add(pos, s, m, prv->l, cur->l);
	}
	else{
		cur->l = prv->l;
		cur->r = new node();
		add(pos, m+1, e, prv->r, cur->r);
	}
}

pi getsum(int s, int e, int ps, int pe, node *p){
	if(e < ps || pe < s) return pi(0, 0);
	if(s <= ps && pe <= e) return pi(p->cnt, p->sum);
	int pm = ps + (pe - ps) / 2;
	pi v1 = getsum(s, e, ps, pm, p->l);
	pi v2 = getsum(s, e, pm+1, pe, p->r);
	return pi(v1.first + v2.first, v1.second + v2.second);
}

int lbnd(int s, int e, int c, node *p){
	if(s == e) return s;
	int m = s + (e-s)/2;
	if(p->l->cnt < c){
		c -= p->l->cnt;
		return lbnd(m+1, e, c, p->r);
	}
	else return lbnd(s, m, c, p->l);
}

lint gettop(int e, int x){
	if(x == 0) return 0;
	int bnd = lbnd(-MAXL, MAXL, x, l[e]);
	pi sum = getsum(-MAXL, bnd-1, -MAXL, MAXL, l[e]);
	return sum.second + (x - sum.first) * bnd;
}

lint getgreed(int s, int x){
	x = max(x, getsum(-MAXL, 0, -MAXL, MAXL, r[s]).first);
	if(x == 0) return 0;
	int bnd = lbnd(-MAXL, MAXL, x, r[s]);
	pi sum = getsum(-MAXL, bnd-1, -MAXL, MAXL, r[s]);
	return sum.second + (x - sum.first) * bnd;
}

int main(){
	char str[100005];
	scanf("%d %d %s",&n,&k,str+1);
	int ans = 0;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		if(str[i] == '('){
			ans += a[i];
			a[i] *= -1;
		}
	}
	if(n % 2 == 1){
		for(int i=1; i<=n; i++) ans += min(a[i], 0);
		cout << ans;
		return 0;
	}
	lint ret = 1e10;
	l[0] = new node();
	r[n+1] = new node();
	init(l[0], -MAXL, MAXL);
	init(r[n+1], -MAXL, MAXL);
	for(int i=1; i<=n; i++){
		l[i] = new node();
		r[n+1-i] = new node();
		add(a[i], -MAXL, MAXL, l[i-1], l[i]);
		add(a[n+1-i], -MAXL, MAXL, r[n+2-i], r[n+1-i]);
	}
	for(int i=0; i<=n; i++){
		int st = 0, ed = i + 1;
		while(st != ed){
			int m = (st+ed)/2;
			int j = 2 * m + (i%2);
			if((i - j) / 2 <= i && (n - i + j) / 2 + k + 1 - (j + j % 2) <= n - i){
				ed = m;
			}
			else st = m+1;
		}
		int s = st;
		int e = i / 2;
		if(s <= e){
			while(s != e){
				int m = (s+e)/2;
				int j1 = i%2 + 2 * m;
				int j2 = j1 + 2;
				if(gettop(i, (i - j1) / 2) + getgreed(i+1, (n - i + j1) / 2 + k + 1 - (j1 + j1 % 2))
						<= gettop(i, (i - j2) / 2) + getgreed(i+1, (n - i + j2) / 2 + k + 1 - (j2 + j2 % 2))){
					e = m;
				}
				else s = m+1;
			}
			int j = i%2 + 2 * s;
			ret = min(ret, gettop(i, (i-j)/2) + getgreed(i+1,  
						(n - i + j) / 2 + k + 1 - (j + j % 2)) );
		}
	}
	ret += ans;
	if(ret > 1e9 + 10){
		cout << "?";
		return 0;
	}
	cout << ret;
}
