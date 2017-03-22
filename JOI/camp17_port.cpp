#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

struct seg2{
	int tree[4200000], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim + 1, -1e9);
	}
	void add(int x, int v){
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
}seg1, seg2;

int n, s[1000005], e[1000005];
int idx[2000005];

int col[1000005];

void dfs(int x, int c){
//	fprintf(stderr, "%d\n", x);
	col[x] = c;
	while(1){
		int t = seg1.query(s[x] + 1, e[x] - 1);
		if(t <= e[x]) break;
		int v = idx[t];
		seg1.add(s[v], -1);
		seg2.add(e[v], -1e9);
		dfs(v, 3-c);
	}
	while(1){
		int t = -seg2.query(s[x] + 1, e[x] - 1);
		if(t >= s[x]) break;
		int v = idx[t];
		seg1.add(s[v], -1);
		seg2.add(e[v], -1e9);
		dfs(v, 3-c);
	}
}

bool solve(vector<pi> &v){
	sort(v.begin(), v.end());
	stack<pi> stk;
	for(int i=0; i<v.size(); i++){
		while(!stk.empty() && stk.top().second < v[i].first){
			stk.pop();
		}
		if(!stk.empty() && stk.top().second > v[i].first && stk.top().second < v[i].second){
			return 0;
		}
		stk.push(v[i]);
	}
	return 1;
}
int main(){
	scanf("%d",&n);
	seg1.init(2*n);
	seg2.init(2*n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&s[i],&e[i]);
		idx[s[i]] = i;
		idx[e[i]] = i;
		seg1.add(s[i], e[i]);
		seg2.add(e[i], -s[i]);
	}
	lint ans = 1;
	for(int i=1; i<=2*n; i++){
		if(!col[idx[i]]){
			seg1.add(s[idx[i]], -1);
			seg2.add(e[idx[i]], -1e9);
			dfs(idx[i], 1);
			ans *= 2;
			ans %= mod;
		}
	}
	vector<pi> l, r;
	for(int i=0; i<n; i++){
		if(col[i] == 1) l.push_back(pi(s[i], e[i]));
		else r.push_back(pi(s[i], e[i]));
	}
	if(!solve(l) || !solve(r)) ans = 0;
	cout << ans;
}

