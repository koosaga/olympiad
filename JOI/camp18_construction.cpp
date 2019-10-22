#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> gph[MAXN];
int n, s[MAXN], e[MAXN], a[MAXN];
int dep[MAXN], din[MAXN], dout[MAXN], piv;
int ddin[MAXN], ddout[MAXN], pivv;
pi spt[18][2 * MAXN];
int lg[2 * MAXN];

int lca(int s, int e){
	if(ddin[s] > ddin[e]) swap(s, e);
	if(ddout[e] <= ddout[s]) return s;
	int st = ddout[s], ed = ddin[e];
	int l = lg[ed - st + 1];
	return min(spt[l][st], spt[l][ed - (1<<l) + 1]).second;
}

void dfs(int x, int p){
	din[x] = ++piv;
	ddin[x] = ++pivv;
	spt[0][pivv] = pi(dep[x] - 1, p);
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
	dout[x] = piv;
	ddout[x] = ++pivv;
	spt[0][pivv] = pi(dep[x] - 1, p);
}

struct segtree{
	int tree[270000], lim;
	void init(){
		memset(tree, 0, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
	int left_max(int s, int e, int thres){
		s += lim;
		e += lim;
		while(s < e){
			if(s % 2 == 1) s++;
			if(e % 2 == 0){
				if(tree[e] > thres){
					while(e < lim){
						if(tree[2*e+1] > thres) e = 2 * e + 1;
						else e = 2 * e;
					}
					return tree[e];
				}
				e--;
			}
			s >>= 1;
			e >>= 1;
		}
		if(s == e && tree[e] > thres){
			while(e < lim){
				if(tree[2*e+1] > thres) e = 2 * e + 1;
				else e = 2 * e;
			}
			return tree[e];
		}
		return 0;
	}
	int right_max(int s, int e, int thres){
		s += lim;
		e += lim;
		while(s < e){
			if(s % 2 == 1){
				if(tree[s] > thres){
					while(s < lim){
						if(tree[2*s] > thres) s = 2 * s;
						else s = 2 * s + 1;
					}
					return tree[s];
				}
				s++;
			}
			if(e % 2 == 0) e--;
			s >>= 1;
			e >>= 1;
		}
		if(s == e && tree[s] > thres){
			while(s < lim){
				if(tree[2*s] > thres) s = 2 * s;
				else s = 2 * s + 1;
			}
			return tree[s];
		}
		return 0;
	}
};

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int main(){
	for(int i=1; i<2*MAXN; i++){
		lg[i] = lg[i-1];
		while((2 << lg[i]) <= i) lg[i]++;
	}
	vector<int> v;
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=1; i<=n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
	for(int i=2; i<=n; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back(e[i]);
		gph[e[i]].push_back(s[i]);
	}
	segtree seg;
	seg.init();
	dfs(1, -1);
	for(int i=1; i<18; i++){
		for(int j=1; j<=2*n; j++){
			spt[i][j] = spt[i-1][j];
			if(j + (1<<(i-1)) <= 2 * n){
				spt[i][j] = min(spt[i][j], spt[i-1][j + (1<<(i-1))]);
			}
		}
	}
	e[1] = 1;
	seg.upd(din[1], 1);
	for(int i=2; i<=n; i++){
		int pos = s[i];
		vector<pi> mem;
		int x;
		while((x = seg.query(din[pos], dout[pos])) != seg.tree[1]){
			int pl = seg.left_max(0, din[pos] - 1, x);
			int pr = seg.right_max(dout[pos] + 1, seg.lim-1, x);
			int nxtpos = 1;
			if(pl > x){
				int aux = lca(pos, e[pl]);
				if(dep[aux] > dep[nxtpos]) nxtpos = aux;
			}
			if(pr > x){
				int aux = lca(pos, e[pr]);
				if(dep[aux] > dep[nxtpos]) nxtpos = aux;
			}
			mem.push_back(pi(dep[pos] - dep[nxtpos], a[e[x]]));
			pos = nxtpos;
		}
		lint ans = 0;
		for(auto &i : mem){
			ans += 1ll * bit.query(i.second - 1) * i.first;
			bit.add(i.second, i.first);
		}
		ans += 1ll * bit.query(a[e[seg.tree[1]]] - 1) * (dep[pos] + 1);
		printf("%lld\n", ans);
		for(auto &i : mem) bit.add(i.second, -i.first);
		seg.upd(din[e[i]], i);
	}
}


