#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <set>
#include <map>
using namespace std;
typedef pair<int, int> pi;

int n, k;
pi a[2005];
int ok[1005][1005];
int ly[1005][1005], hy[1005][1005], lx[1005][1005], hx[1005][1005];
 
struct rmq{
	int tree[2050], lim;
	void init(int n){
		fill(tree, tree + 2050, -1e9);
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		x += lim;
		tree[x] = max(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = -1e9;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}rmq;
 
struct seg{
	struct node{
		int ret, l, r;
	}tree[2050];
	int lim;
	node base;
	node merge(node &l, node &r){
		node ret;
		ret.ret = max(l.ret, r.ret);
		ret.ret = max(ret.ret, r.r - l.l);
		ret.r = max(r.r, l.r);
		ret.l = min(l.l, r.l);
		return ret;
	}
	void init(int n){
		base.r = base.ret = -1e9;
		base.l = 1e9;
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2050, base);
	}
	void add(int x, int f1, int f2){
		node v;
		v.ret = -1e9, v.l = f1, v.r = f2;
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		node lv = base, rv = base;
		while(s < e){
			if(s%2 == 1) lv = merge(lv, tree[s++]);
			if(e%2 == 0) rv = merge(tree[e--], rv);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) lv = merge(lv, tree[s]);
		return merge(lv, rv).ret;
	}
}seg;
 
vector<int> swp[1005];

int solve(){
	memset(ok, 0, sizeof(ok));
	memset(hx, 0x3f, sizeof(hx));
	memset(hy, 0x3f, sizeof(hy));
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for(int i=0; i<k; i++){
		ok[a[i].first][a[i].second] = 1;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(ok[i][j]){
				lx[i][j] = i;
			}
			else{
				lx[i][j] = lx[i-1][j];
			}
			if(ok[j][i]){
				ly[j][i] = i;
			}
			else{
				ly[j][i] = ly[j][i-1];
			}
		}
	}
	for(int i=n; i; i--){
		for(int j=1; j<=n; j++){
			if(ok[i][j]){
				hx[i][j] = i;
			}
			else{
				hx[i][j] = hx[i+1][j];
			}
			if(ok[j][i]){
				hy[j][i] = i;
			}
			else{
				hy[j][i] = hy[j][i+1];
			}
		}
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		rmq.init(n);
		seg.init(n);
		set<int> s;
		for(int j=0; j<=n; j++) swp[j].clear();
		for(int j=1; j<=n; j++){
			if(i - 1 > lx[i][j]){
				rmq.add(j, -lx[i][j] - j);
			}
			s.insert(j);
			swp[min(i-1, lx[i][j])].push_back(j);
			seg.add(j, 2 * j + lx[i][j], 2 * j);
		}
		int p = 0;
		for(int j=i-1; j; j--){
			for(auto &k : swp[j]){
				s.erase(k);
				seg.add(k, 1e9, -1e9);
			}
			vector<int> v;
			v.push_back(0);
			int p1 = hy[i][1], p2 = hy[j][1];
			while(p1 <= n || p2 <= n){
				if(p1 <= p2){
					v.push_back(p1);
					p1 = hy[i][p1+1];
				}
				else{
					v.push_back(p2);
					p2 = hy[j][p2+1];
				}
			}
			v.push_back(n+1);
			for(int k=1; k<=n; k=hy[j][k] + 1){
				if(ok[j][k-1]){
					int bound = min(hy[j][k], hy[i][k]);
					auto t = s.lower_bound(bound);
					if(t != s.begin()){
						t--;
						if(*t > k){
							ret = max(ret, i + *t + rmq.query(ly[i][k]+1, k-1) + i - j + *t - k);
						}
					}
				}
			}
			for(int k=1; k<v.size(); k++){
				ret = max(ret, i + i - j - 1 + seg.query(v[k-1] + 1, v[k] - 1));
			}
		}
	}
	return ret;
}
 
int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<k; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	int ret = 0;
	for(int i=0; i<4; i++){
		ret = max(ret, solve());
		for(int j=0; j<k; j++){
			a[j].second = n + 1 - a[j].second;
		}
		ret = max(ret, solve());
		for(int j=0; j<k; j++){
			a[j].second = n + 1 - a[j].second;
		}
		for(int j=0; j<k; j++){
			a[j] = pi(a[j].second, n + 1 - a[j].first);
		}
	}
	printf("%d",ret);
}