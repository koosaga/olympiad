#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 50005;
const int MAXT = 132000;

int n, c;
pi a[MAXN];

bool update = true;
bool vis[MAXN];

int ptr;
vector<int> dfn;

int minHP[MAXN], cnt[MAXN];

struct seg{
	int lim;
	pi tree[MAXT];
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(2e9, 2e9));
	}
	void upd(int x, int v){
		tree[x + lim] = pi(v, x);
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(2e9, 2e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

int pop(int s, int e){
	while(true){
		auto val = seg.query(s, e);
		if(val.first > 1e9) return -1;
		if(vis[val.second]){
			seg.upd(val.second, 2e9);
		}
		else return val.second;
	}
}

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	dfn.push_back(x);
	while(ptr < n && a[ptr].first < a[x].first - c){
		dfs(ptr++);
	}
	int s = lower_bound(a, a + n, pi(a[x].first - c, -1)) - a;
	int e = lower_bound(a, a + n, pi(a[x].first + c + 1, -1)) - a;
	while(true){
		auto y = pop(s, e - 1);
		if(y != -1 && a[y].second < a[x].second) dfs(y);
		else break;
	}
}

int main(){
	scanf("%d %d",&n,&c);
	vector<int> yval;
	for(int i = 0; i < n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		yval.push_back(a[i].second);
	}
	sort(a, a + n);
	sort(all(yval));
	fill(minHP, minHP + MAXN, 1e9);
	seg.init(n);
	for(int i = 0; i < n; i++){
		a[i].second = lower_bound(all(yval), a[i].second) - yval.begin();
		minHP[a[i].second] = min(minHP[a[i].second], a[i].first);
		seg.upd(i, a[i].second);
	}
	for(int i = 0; i < n; i++){
		if(a[i].first <= minHP[a[i].second] + c) cnt[a[i].second]++;
	}
	while(update){
		while(ptr < n && vis[ptr]) ptr++;
		if(ptr == n) break;
		int maxpos = lower_bound(a, a + n, pi(a[ptr].first + c + 1, -1)) - a;
		int cur = pop(ptr, maxpos - 1);
		dfs(cur);
		for(auto &i : dfn){
			if(a[i].first <= minHP[a[i].second] + c){
				cnt[a[i].second]--;
				if(cnt[a[i].second] == 0) update = false;
			}
		}
		dfn.clear();
	}
	cout << count(vis, vis + n, 1) << endl;
}

