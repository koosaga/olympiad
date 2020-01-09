#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 10005;

struct intv{
	int s, e, x;
}a[MAXN];
int n;

bool trial(lint x){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=0; i<n-1; i++){
		lint provide = a[i].s * x;
		pq.emplace(a[i].e * x, a[i].x);
		while(sz(pq) && provide < a[i + 1].s * x){
			auto l = pq.top();
			pq.pop();
			if(l.first <= provide) return 0;
			lint dx = min(l.second, min(a[i + 1].s * x, l.first) - provide);
			provide += dx;
			l.second -= dx;
			if(l.second > 0){
				pq.push(l);
				break;
			}
		}
	}
	pq.emplace(a[n-1].e * x, a[n-1].x);
	lint provide = a[n - 1].s * x;
	while(sz(pq)){
		provide += pq.top().second;
		if(provide > pq.top().first) return 0;
		pq.pop();
	}
	return 1;
}

int main(){
	int tc; cin >> tc;
	while(tc--){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
	sort(a, a + n, [&](const intv &x, const intv &y){
		return x.s < y.s;
	});
	int s = 0, e = 1e8;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	cout << s << endl;
	}
}

