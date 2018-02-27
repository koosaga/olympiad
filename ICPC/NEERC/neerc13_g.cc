#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
typedef long long lint;
typedef pair<int, int> pi;
using real_t = long double;

int n, m;
real_t ret[MAXN];
real_t alp;
pi a[MAXN], b[MAXN];

real_t func(pi x){
	return x.second + alp * x.first;
}

struct seg{
	pi s, e;
	real_t arg1, arg2;
};

vector<seg> v;

void Place(seg s, real_t arg, int p){
	real_t st = func(s.s);
	real_t ed = func(s.e);
	real_t argpos = (arg - st) / (ed - st);
	ret[p] = s.s.first + (s.e.first - s.s.first) * argpos;
}

int main(){
	freopen("green.in", "r", stdin);
	freopen("green.out", "w", stdout);
	int tmp;
	scanf("%d %d %d",&n,&m,&tmp);
	alp = tan(acos(-1) / 180 * tmp);
	for(int i=0; i<n; i++) scanf("%d",&a[i].first), a[i].second = i;
	sort(a, a+n);
	reverse(a, a+n);
	for(int i=0; i<m; i++) scanf("%d %d",&b[i].first,&b[i].second);
	real_t curarg = func(b[0]);
	for(int i=1; i<m; i++){
		if(curarg >= func(b[i])) continue;
		v.push_back({b[i-1], b[i], curarg, func(b[i])});
		curarg = func(b[i]);
	}
	reverse(v.begin(), v.end());


	real_t ans = curarg - func(b[0]) + a[0].first;
	real_t sum = 0;
	for(int i=0; i<n; i++) sum += a[i].first;
	ans = min(ans, sum);
	printf("%.15Lf\n", ans);
	int p = 0;
	curarg += a[0].first;
	for(auto &i : v){
		while(p < n && curarg - a[p].first >= i.arg1){
			curarg -= a[p].first;
			Place(i, curarg, a[p].second);
			p++;
		}
	}
	while(p < n){
		ret[a[p].second] = b[0].first;
		p++;
	}
	for(int i=0; i<n; i++) printf("%.15Lf\n", ret[i]);
}
