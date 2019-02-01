#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 500005;

int n, m, a[MAXN];

struct intv{
	int s, e; 
	lint d, b;
	bool operator<(const intv &i)const{
		return e < i.e;
	}
};

#define y1 fuck_gcc

lint ps[MAXN];
lint get_erase(int s, int e, lint x1, lint y1, lint x2, lint y2){
	lint ans = (y1 - y2) * (e - s + 1);
	ans += (x2 - x1) * (ps[e+1] - ps[s]);
	return ans;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	sort(a, a+n);
	reverse(a, a+n);
	for(int i=0; i<n; i++) ps[i+1] = ps[i] + a[i];
	set<intv> s;
	s.insert({0, n-1, 0, 0});
	while(m--){
		lint t, x;
		scanf("%lld %lld",&t,&x);
		auto l = s.begin();
		int ins = -1;
		lint ans = 0;
		while(s.size()){
			lint k = (x - l->b + t - l->d - 1) / (t - l->d);
			if(a[l->s] < k) break;
			if(a[l->e] >= k){
				ins = l->e;
				ans += get_erase(l->s, l->e, l->d, l->b, t, x);
				s.erase(l);
				l = s.begin();
				continue;
			}
			if(a[l->e] < k){
				int st = l->s, ed = l->e;
				while(st != ed){
					int m = (st+ed)/2;
					if(a[m] < k) ed = m;
					else st = m+1;
				}
				auto k = *l;
				k.s = st;
				ins = st - 1;
				ans += get_erase(l->s, st - 1, l->d, l->b, t, x);
				s.erase(l);
				s.insert(k);
				break;
			}
		}
		if(~ins) s.insert({0, ins, t, x});
		printf("%lld\n", ans);
	}
}
