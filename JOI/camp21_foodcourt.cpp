#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 250005;
const int MAXT = 530000;

struct fen{
	lint tree[MAXN];
	void add(int x, lint v){
		for(int i = x; i < MAXN; i += i & -i) tree[i] += v;
	}
	lint query(int x){
		lint ret = 0;
		for(int i = x; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int kth(lint val){
		int pos = 0;
		for(int i = 17; i >= 0; i--){
			if(pos + (1<<i) < MAXN && tree[pos + (1<<i)] < val){
				pos += (1<<i);
				val -= tree[pos];
			}
		}
		return pos + 1;
	}
}fen;

struct seg{
	struct node{
		lint smax, sum;
		node operator+(const node &n)const{
			node ret = {max(smax + n.sum, n.smax), sum + n.sum};
			return ret;
		}
	}tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, lint v){
		x += lim;
		tree[x] = (node){max(0ll, v), v};
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	node query(int s, int e){
		s += lim;
		e += lim;
		node l = {0, 0}, r = {0, 0};
		while(s < e){
			if(s%2 == 1) l = l + tree[s++];
			if(e%2 == 0) r = tree[e--] + r;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) l = l + tree[s];
		return l + r;
	}
}seg;

int n, q;

vector<pi> quer[MAXN], upd[MAXN], fwupd[MAXN];
lint mp[MAXN];
lint ret[MAXN];
lint prv[MAXN];

int main(){
	memset(ret, -1, sizeof(ret));
	scanf("%d %*d %d",&n,&q);
	for(int i = 1; i <= q; i++){
		int t; scanf("%d",&t);
		if(t == 3){
			lint a, b;
			scanf("%lld %lld",&a,&b);
			quer[a].emplace_back(i, b);
		}
		if(t == 2){
			lint l, r, k;
			scanf("%lld %lld %lld",&l,&r,&k);
			upd[l].emplace_back(i, -k);
			upd[r + 1].emplace_back(i, 0);
		}
		if(t == 1){
			lint l, r, c, k;
			scanf("%lld %lld %lld %lld",&l,&r,&c,&k);
			mp[i] = c;
			upd[l].emplace_back(i, k);
			upd[r + 1].emplace_back(i, 0);
			fwupd[l].emplace_back(i, k);
			fwupd[r + 1].emplace_back(i, -k);
		}
	}
	seg.init(q);
	for(int i = 1; i <= n; i++){
		for(auto &[pos, val] : upd[i]){
			seg.upd(pos, val);
		}
		for(auto &[pos, val] : fwupd[i]){
			fen.add(pos, val);
		}
		for(auto &[pos, val] : quer[i]){
			auto cur_ppl = seg.query(1, pos);
			if(cur_ppl.smax >= val){
				lint kth = fen.query(pos) - (cur_ppl.smax - val);
				ret[pos] = mp[fen.kth(kth)];
			}
			else{
				ret[pos] = 0;
			}
		}
	}
	for(int i = 1; i <= q; i++){
		if(~ret[i]) printf("%lld\n", ret[i]);
	}
}
