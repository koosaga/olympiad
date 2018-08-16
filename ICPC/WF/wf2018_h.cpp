#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;

int n, w, h, nxt[4 * MAXN];

pi get_pos(pi v){
	int x, y; tie(x, y) = v;
	if(x == 0) return pi(0, y);
	if(y == h) return pi(1, x);
	if(x == w) return pi(2, h - y);
	if(y == 0) return pi(3, w - x);
	assert(0);
}

vector<pi> v;
pi rs[MAXN], re[MAXN];
int s[MAXN], e[MAXN];

void Do(int p){
	int ns = -1e9, ne = 1e9;
	for(int i=0; i<n; i++){
		while(s[i] <= p) s[i] += n * 2;
		while(e[i] <= p) e[i] += n * 2;
		if(s[i] > e[i]) swap(s[i], e[i]);
		ns = max(ns, s[i]);
		ne = min(ne, e[i]);
	}
	assert(ns < ne);
	auto l = v[p];
	auto r = v[ns % (2 * n)];
	auto pr = [&](pi l){
		if(l.first == 0) printf("0 %f ", l.second + 0.1);
		if(l.first == 1) printf("%f %d ", l.second + 0.1, h);
		if(l.first == 2) printf("%d %f ", w, h - l.second - 0.1);
		if(l.first == 3) printf("%f 0 ", w - l.second - 0.1);
	};
	puts("1");
	pr(l); pr(r);
}

int main(){
	scanf("%d %d %d",&n,&w,&h);
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&rs[i].first,&rs[i].second,&re[i].first,&re[i].second);
		v.push_back(get_pos(rs[i]));
		v.push_back(get_pos(re[i]));
	}
	sort(v.begin(), v.end());
	memset(nxt, 0x3f, sizeof(nxt));
	for(int i=0; i<n; i++){
		s[i] = lower_bound(v.begin(), v.end(), get_pos(rs[i])) - v.begin();
		e[i] = lower_bound(v.begin(), v.end(), get_pos(re[i])) - v.begin();
		if(s[i] > e[i]){
			swap(s[i], e[i]);
			swap(rs[i], re[i]);
		}
		nxt[s[i]] = min(nxt[s[i]], e[i]);
		nxt[e[i]] = min(nxt[e[i]], s[i] + 2 * n);
		nxt[s[i] + 2 * n] = min(nxt[s[i] + 2 * n], e[i] + 2 * n);
	}
	for(int i=4*n-1; i>=0; i--){
		nxt[i] = min(nxt[i], nxt[i+1]);
	}
	for(int i=0; i<2*n; i++){
		if(nxt[i+1] > 1e7 || nxt[nxt[i+1]] > i + n*2){
			Do(i);
			return 0;
		}
	}
	cout << 2 << endl;
	printf("0.1 0 %d %f\n", w, h - 0.1);
	printf("%d 0.1 0.1 %d\n", w, h);
}

