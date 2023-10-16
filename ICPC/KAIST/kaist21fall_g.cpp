#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;

struct node{
	lint sum, opt, pfx, sfx;
	node(){
		sum = opt = pfx = sfx = 0;
	}
	node(lint x){
		sum = x;
		opt = pfx = sfx = min(x, 0ll);
	}
	node operator+(const node &n)const{
		node ret;
		ret.sum = sum + n.sum;
		ret.pfx = min(pfx, sum + n.pfx);
		ret.sfx = min(n.sfx, n.sum + sfx);
		ret.opt = min({opt, n.opt, sfx + n.pfx});
		return ret;
	}
};

struct seg{
	vector<node> tree;
	int lim;
	void init(vector<int> &a){
		for(lim = 1; lim <= sz(a); lim <<= 1);
		tree.resize(2 * lim + 10, node(0));
		for(int i = 0; i < sz(a); i++){
			tree[i + lim] = node(a[i]);
		}
		for(int i = lim-1; i; i--) tree[i] = tree[2*i] + tree[2*i+1];
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = node(v);
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	node query(int s, int e){
		s += lim;
		e += lim;
		node L(0), R(0);
		while(s < e){
			if(s%2 == 1) L = L + tree[s++];
			if(e%2 == 0) R = tree[e--] + R;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) L = L + tree[s];
		return L + R;
	}
}seg;

int main(){
	int n, q;
	scanf("%d %d",&n,&q);
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		scanf("%d",&a[i]);
	}
	seg.init(a);
	auto query = [&](int l, int r, int x){
		int h = x;
		// turn 1
		{
			auto qr = seg.query(0, l - 1);
			if(qr.opt <= -x) return 0;
			h += qr.sfx;
		}
		// turn 2 
		{
			int div10 = (x + 9) / 10;
			auto qr = node(h - x) + seg.query(l, r);
			if(qr.opt <= div10 - x) h = div10;
			else{
				h = x + qr.sfx;
			}
		}
		// turn 3
		{
			auto qr = node(h - x) + seg.query(r + 1, n - 1);
			if(qr.opt <= -x) return 0;
			return (int)(x + qr.sfx);
		}
	};
	for(int i = 0; i < q; i++){
		int t; scanf("%d",&t);
		if(t == 2){
			int i, x; scanf("%d %d",&i,&x);
			seg.upd(i-1, x);
		}
		else{
			int l, r, x; scanf("%d %d %d",&l,&r,&x);
			l--; r--;
			printf("%d\n", query(l, r, x));
		}
	}
}
