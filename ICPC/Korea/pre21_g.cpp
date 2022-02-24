#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 20005;

double cur;

struct line{
	int sx, ex, sy, ey, idx;
	long double pos(int cur)const{
		if(sx == ex) return 1.0L * (sy + ey) / 2;
		if(cur == sx) return sy;
		if(cur == ex) return ey;
		return sy + 1.0L * (ey - sy) * (cur - sx) / (ex - sx);
	}
	bool operator<(const line &l)const{
		if(idx == l.idx) return 0;
		int p = max(sx, l.sx);
		if(fabs(pos(p) - l.pos(p)) < 1e-20L) return idx < l.idx;
		return pos(p) < l.pos(p);
	}
}a[MAXN];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int sgn(lint x){
	if(x == 0) return 0;
	return x > 0 ? 1 : -1;
}

int n;
vector<int> gph[MAXN];
int dp[MAXN];
set<line>::iterator where[MAXN];

int f(int x){
	if(~dp[x]) return dp[x];
	int ret = 0;
	for(auto &y : gph[x]) ret = max(ret, f(y));
	return dp[x] = ret + 1;
}

int main(){
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		scanf("%d %d %d %d",&a[i].sy,&a[i].sx,&a[i].ey,&a[i].ex);
		if(pi(a[i].sx, a[i].sy) > pi(a[i].ex, a[i].ey)){
			swap(a[i].sx, a[i].ex);
			swap(a[i].sy, a[i].ey);
		}
		a[i].idx = i;
	}
	vector<pi> events;
	for(int i = 0; i < n; i++){
		events.emplace_back(a[i].sx, ~i);
		events.emplace_back(a[i].ex, i);
	}
	sort(all(events));
	set<line> s;
	for(auto &i : events){
		int p = i.second;
		if(p < 0) p = ~p;
		if(i.second < 0){
			auto x = s.lower_bound(a[p]);
			if(x != s.end()){
				gph[a[p].idx].push_back(x->idx);
			}
			if(x != s.begin()){
				gph[prev(x)->idx].push_back(a[p].idx);
			}
			where[p] = s.insert(x, a[p]);
		}
		else{
			auto x = s.erase(where[p]);
			if(x != s.begin() && x != s.end()){
				gph[prev(x)->idx].push_back(x->idx);
			}
		}
	}
	int ret = 0;
	memset(dp, -1, sizeof(dp));
	for(int i = 0; i < n; i++){
		ret = max(ret, f(i));
	}
	printf("%d\n", ret);
}

