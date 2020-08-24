#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 100005;

inline int frcmp(int x1, int d1, int x2, int d2){
	lint p = 1ll * x2 * d1 - 1ll * x1 * d2;
	if(p > 0) return 1;
	if(p < 0) return -1;
	return 0;
}

struct pnt{
	int x, y, d;
	bool operator<(const pnt &b)const{
		int t = frcmp(x, d, b.x, b.d);
		if(t != 0) return t > 0;
		return frcmp(y, d, b.y, b.d) > 0;
	}
	bool operator==(const pnt &p)const{
		return x == p.x && y == p.y && d == p.d;
	}
	bool operator>(const pnt &b)const{
		return b < *this;
	}
};

pnt input(){
	int x, y, z; scanf("%d %d %d",&x,&y,&z);
	int g = gcd(x, gcd(y, z));
	x /= g; y /= g; z /= g;
	return (pnt){x, y, x + y + z};
}

inline int ccw(pnt p1, pnt p2, pnt p3){
	lint lhs = 1ll * p1.d * p2.x * p3.y - 1ll * p1.x * p2.d * p3.y - 1ll * p1.y * p2.x * p3.d;
	lint rhs = 1ll * p1.d * p2.y * p3.x - 1ll * p1.x * p2.y * p3.d - 1ll * p1.y * p2.d * p3.x;
	if(lhs > rhs) return 1;
	if(lhs < rhs) return -1;
	return 0;
}

pnt c, a[MAXN];
bool mark[MAXN];
int cnt;


int type(pnt p){
	if(c == p) return -1;
	if(c < p) return 0;
	return 1;
}

auto cmp = [](pnt a, pnt b){
	if(type(a) == type(b)){
		return ccw(c, a, b) > 0;
	}
	return ccw(c, a, b) < 0;
};

vector<multiset<pnt,  decltype(cmp)>> s;


bool in_cvxh(){
	if(sz(s[1]) == 0 || sz(s[0]) == 0) return 0;
	if(ccw(c, *s[0].rbegin(), *s[1].begin()) < 0) return 0;
	if(ccw(c, *s[1].rbegin(), *s[0].begin()) < 0) return 0;
	return 1;
}

int main(){
	int onecnt = 0;
	int collapse = 0;
	for(int i=0; i<2; i++){
		s.emplace_back(cmp);
	}
	c = input();
	int q; scanf("%d",&q);
	char buf[69];
	while(q--){
		auto fresh = [&](int v, pnt p){
			auto it = s[v].lower_bound(p);
			if(it != s[v].end() && ccw(c, p, *it) == 0) return false;
			return true;
		};
		scanf("%s", buf);
		if(*buf == 'A'){
			a[++cnt] = input();
			int v = type(a[cnt]);
			if(v == -1) onecnt++;
			else{
				if(fresh(v, a[cnt])){
					auto it = s[v^1].lower_bound(a[cnt]);
					if(it != s[v^1].end() && ccw(c, *it, a[cnt]) == 0) collapse++;
				}
				s[v].insert(a[cnt]);
			}
		}
		else{
			int x; scanf("%d",&x);
			mark[x] = 1;
			int v = type(a[x]);
			if(v == -1) onecnt--;
			else{
				s[v].erase(s[v].find(a[x]));
				if(fresh(v, a[x])){
					auto it = s[v^1].lower_bound(a[x]);
					if(it != s[v^1].end() && ccw(c, *it, a[x]) == 0) collapse--;
				}
			}
		}
		if(onecnt > 0) puts("1");
		else if(collapse > 0) puts("2");
		else puts(in_cvxh() ? "3" : "0");
	}
}