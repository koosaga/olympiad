#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
int l[100005], r[100005];
int rev[100005], vis[100005];
int pos[200005];

struct segmax{
	int tree[530000], lim;
	void init(int n){
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
}seg1;

struct segmin{
	int tree[530000], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		memset(tree,0x3f,sizeof(tree));
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg2;

void dfs(int x, int c){
	vis[x] = c;
	while(1){
		int p = seg1.query(l[x] + 1, r[x] - 1);
		if(p <= r[x]) break;
		seg1.upd(l[pos[p]], -1e9);
		seg2.upd(r[pos[p]], 1e9);
		dfs(pos[p], 3 - c);
	}
	while(1){
		int p = seg2.query(l[x] + 1, r[x] - 1);
		if(p >= l[x]) break;
		seg1.upd(l[pos[p]], -1e9);
		seg2.upd(r[pos[p]], 1e9);
		dfs(pos[p], 3 - c);
	}
}

bool ok(vector<pi> &seg){
	vector<pi> ev;
	for(auto &i : seg){
		ev.push_back(pi(i.first, -1));
		ev.push_back(pi(i.second, i.first));
	}
	sort(ev.begin(), ev.end());
	stack<int> stk;
	for(auto &i : ev){
		if(i.second == -1) stk.push(i.first);
		else{
			if(stk.empty() || stk.top() != i.second) return 0;
			stk.pop();
		}
	}
	return stk.empty();
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		rev[x] = i;
	}
	int p = 0, q = 0;
	for(int i=1; i<=n; i++){
		while(p < rev[i]){
			p++;
			q++;
			l[p] = q;
		}
		r[rev[i]] = ++q;
	}
	seg1.init(2*n);
	seg2.init(2*n);
	for(int i=1; i<=n; i++){
		pos[l[i]] = pos[r[i]] = i;
		seg1.upd(l[i], r[i]);
		seg2.upd(r[i], l[i]);
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]) dfs(i, 1);
	}
	vector<pi> seg[2];
	for(int i=1; i<=n; i++){
		seg[vis[i] - 1].push_back(pi(l[i], r[i]));
	}
	if(!ok(seg[0]) || !ok(seg[1])) puts("NIE");
	else{
		puts("TAK");
		for(int i=1; i<=n; i++) printf("%d ", vis[i]);
	}
}
