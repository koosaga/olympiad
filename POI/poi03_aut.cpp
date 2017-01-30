#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int m, n, col[20005];
pi a[20005];

struct seg1{
	set<pi> danmal[20005];
	pi tree[66000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 66000, pi(-1e9, 1e9));
	}
	void add(int x, pi c){
		danmal[x].insert(c);
		tree[x + lim] = *danmal[x].rbegin();
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	void remove(int x, pi c){
		danmal[x].erase(c);
		if(danmal[x].empty()) tree[x + lim] = pi(-1e9, 1e9);
		else tree[x + lim] = *danmal[x].rbegin();
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-1e9, 1e9);
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

struct seg2{
	set<pi> danmal[20005];
	pi tree[66000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 66000, pi(1e9, 1e9));
	}
	void add(int x, pi c){
		danmal[x].insert(c);
		tree[x + lim] = *danmal[x].begin();
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	void remove(int x, pi c){
		danmal[x].erase(c);
		if(danmal[x].empty()) tree[x + lim] = pi(1e9, 1e9);
		else tree[x + lim] = *danmal[x].begin();
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, 1e9);
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
	seg1.remove(a[x].first, pi(a[x].second, x));
	seg2.remove(a[x].second, pi(a[x].first, x));
	col[x] = c;
	while(1){
		auto k = seg1.query(a[x].first+1, a[x].second-1);
		if(k.first > a[x].second) dfs(k.second, 3-c);
		else break;
	}
	while(1){
		auto k = seg2.query(a[x].first+1, a[x].second-1);
		if(k.first < a[x].first) dfs(k.second, 3-c);
		else break;
	}
}

bool check(vector<pi> v){
	sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
		return pi(a.first, -a.second) < pi(b.first, -b.second);
	});
	stack<pi> stk;
	for(int i=0; i<v.size(); i++){
		while(!stk.empty() && stk.top().second < v[i].second){
			if(stk.top().second > v[i].first) return 0;
			stk.pop();
		}
		stk.push(v[i]);
	}
	return 1;
}
int main(){
	cin >> m >> n;
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	seg1.init(m);
	seg2.init(m);
	for(int i=0; i<n; i++){
		seg1.add(a[i].first, pi(a[i].second, i));
		seg2.add(a[i].second, pi(a[i].first, i));
	}
	for(int i=0; i<n; i++){
		if(!col[i]) dfs(i, 1);
	}
	vector<pi> c1, c2;
	for(int i=0; i<n; i++){
		if(col[i] == 1) c1.push_back(a[i]);
		else c2.push_back(a[i]);
	}
	if(check(c1) == 0 || check(c2) == 0){
		puts("NIE");
		return 0;
	}
	for(int i=0; i<n; i++){
		puts(col[i] == 1 ? "N" : "S");
	}
}
