#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 250005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i = x + 1; i < MAXN; i += i & -i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i = x + 1; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	void clear(){
		memset(tree, 0, sizeof(tree));
	}
}bit;

int n, k;
pi a[MAXN];
vector<lint> v;

bool trial(lint m){
	int j = 0;
	int ret = 0;
	bit.clear();
	for(int i = 0; i < n; i++){
		while(a[i].first - a[j].first > m){
			bit.add(a[j++].second, -1);
		}
		int l = lower_bound(all(v), v[a[i].second] - m) - v.begin();
		int r = upper_bound(all(v), v[a[i].second] + m) - v.begin();
		ret += bit.query(r - 1) - bit.query(l - 1);
		if(ret > k) return 0;
		bit.add(a[i].second, +1);
	}
	return 1;
}

void report(lint m){
	vector<lint> ans;
	int j = 0;
	set<pi> s;
	for(int i = 0; i < n; i++){
		while(a[i].first - a[j].first > m){
			s.erase(pi(v[a[j].second], j));
			j++;
		}
		auto it = s.lower_bound(pi(v[a[i].second] - m, -1));
		while(it != s.end() && it->first <= v[a[i].second] + m){
			int j = it->second;
			lint dist = max(abs(a[i].first - a[j].first), abs(v[a[i].second] - v[a[j].second]));
			ans.push_back(dist);
			it++;
		}
		s.insert(pi(v[a[i].second], i));
	}
	sort(all(ans));
	while(sz(ans) < k) ans.push_back(m + 1);
	for(auto &i : ans) printf("%lld\n", i);
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i = 0; i < n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[i] = pi(x-y, x+y);
		v.push_back(x+y);
	}
	sort(a, a + n);
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for(int i = 0; i < n; i++){
		a[i].second = lower_bound(all(v), a[i].second) - v.begin();
	}
	lint s = 0, e = 4e9;
	while(s != e){
		lint m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m - 1;
	}
	report(s);
}
