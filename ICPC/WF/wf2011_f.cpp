#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

const lint is_query = -(1LL<<62);

struct Line {
	lint m, b;
	mutable function<const Line*()> succ;
	bool operator<(const Line& rhs) const {
		if (rhs.b != is_query) return m < rhs.m;
		const Line* s = succ();
		if (!s) return 0;
		lint x = rhs.m;
		return b - s->b < (s->m - m) * x;
	}
};

struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
	bool bad(iterator y) {
		auto z = next(y);
		if (y == begin()) {
			if (z == end()) return 0;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = prev(y);
		if (z == end()) return y->m == x->m && y->b <= x->b;
		return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
	}
	void insert_line(lint m, lint b) {
		auto y = insert({ m, b });
		y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
		if (bad(y)) { erase(y); return; }
		while (next(y) != end() && bad(next(y))) erase(next(y));
		while (y != begin() && bad(prev(y))) erase(prev(y));
	}
	lint query(lint x) {
		auto l = *lower_bound((Line) { x, is_query });
		return l.m * x + l.b;
	}
}H;

int cases;
int n, c;
 
struct elem{int d, p, r, g;}a[100005];
 
bool solve(){
	scanf("%d %d",&n,&c);
	if(n == 0) return 0;
	scanf("%d",&a[n+1].d);
	a[n+1].d++;
	a[n+1].p = 0;
	a[n+1].r = 0;
	a[n+1].g = 0;
	for(int i=1; i<=n; i++){
		scanf("%d %d %d %d",&a[i].d,&a[i].p,&a[i].r,&a[i].g);
	}
	sort(a+1,a+n+1,[](const elem &a, const elem &b){return a.d < b.d;});
	H.clear();
	H.insert_line(0, c);
	lint dp, ans = c;
	for(int i=1; i<=n+1; i++){
		dp = H.query(a[i].d) - a[i].p;
		ans = max(ans, dp);
		if(dp >= 0) H.insert_line(a[i].g, dp + a[i].r - 1ll * (a[i].d + 1) * a[i].g);
	}
	printf("Case %d: %lld\n",++cases, ans);
	return 1;
}

int main(){
	while(solve());
}
