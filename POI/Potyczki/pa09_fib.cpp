#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXT = 270000;
const int mod = 1e9 + 7;

struct mtrx{
	lint a[2][2];
	mtrx(){
		a[0][0] = a[1][1] = 1;
		a[1][0] = a[0][1] = 0;
	}
	mtrx(int x){
		a[0][0] = a[1][1] = x;
		a[1][0] = a[0][1] = 0;
	}
	mtrx operator+(const mtrx &m){
		mtrx ret;
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				ret.a[i][j] = (a[i][j] + m.a[i][j]) % mod;
			}
		}
		return ret;
	}
	mtrx operator*(const mtrx &m){
		mtrx ret(0);
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				for(int k=0; k<2; k++){
					ret.a[j][k] = (ret.a[j][k] + a[j][i] * m.a[i][k]) % mod;
				}
			}
		}
		return ret;
	}
};

mtrx fib;

struct node{
	mtrx sum;
	mtrx lmul;
}tree[MAXT];

int n;

struct seg{
	void init(int s = 1, int e = n, int p = 1){
		if(s == e) return;
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		tree[p].sum = (tree[2*p].sum + tree[2*p+1].sum);
	}
	void lazydown(int p){
		for(int j=2*p; j<2*p+2; j++){
			tree[j].sum = tree[j].sum * tree[p].lmul;
			tree[j].lmul = tree[j].lmul * tree[p].lmul;
		}
		tree[p].lmul = mtrx(1);
	}
	void add(int s, int e, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].sum = tree[p].sum * fib;
			tree[p].lmul = tree[p].lmul * fib;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p);
		add(s, e, pm+1, pe, 2*p+1);
		tree[p].sum = (tree[2*p].sum + tree[2*p+1].sum);
	}
	mtrx query(int s, int e, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return mtrx(0);
		if(s <= ps && pe <= e) return tree[p].sum;
		int pm = (ps+pe)/2;
		lazydown(p);
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
}seg;

int main(){
	fib.a[0][0] = 0;
	fib.a[0][1] = 1;
	fib.a[1][0] = 1;
	fib.a[1][1] = 1;
	int q;
	scanf("%d %d",&n,&q);
	seg.init();
	char buf[5];
	while(q--){
		scanf("%s", buf);
		int l, r; scanf("%d %d",&l,&r);
		if(*buf == 'D') seg.add(l, r);
		else printf("%lld\n", seg.query(l, r).a[0][1]);
	}
}
