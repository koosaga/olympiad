#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 300005;
const int MAXT = 1050000;
const int inf = 1e9 + 1000;

struct seg{
	int lim;
	pi tree[MAXT];
	void init(int n, int *v){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(inf, 0));
		for(int i=0; i<n; i++) tree[i + lim] = pi(v[i], i);
		for(int i=lim-1; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(inf, 0);
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

struct rec{
	int l, r, h;
};

int n, a[MAXN], step[MAXN];
lint l, r;
vector<rec> rect;

void dnc(int s, int e){
	if(s > e) return;
	auto m = seg.query(s, e);
	dnc(s, m.second - 1);
	dnc(m.second + 1, e);
	rect.push_back({m.second - s, e - m.second, m.first});
}

lint bin(int x){
	if(x < 0) return 0;
	return 1ll * (x + 1) * (x + 2) / 2;
}

lint get(int l, int r, int v){
	return bin(v) - bin(v - l - 1) - bin(v - r - 1) + bin(v - l - r - 2);
}

lint trial(lint v){
	lint ans = 0;
	for(int i=0; i<rect.size(); i++){
		lint H = v / rect[i].h;
		H = min(H, rect[i].r + rect[i].l + 1ll);
		step[i] = H;
	}
	for(int i=0; i<rect.size(); i++){
		ans += get(rect[i].l, rect[i].r, step[i] - 1);
	}
	return ans;
}

void printAndMove(lint c, lint v){
	while(c && l <= r){
		printf("%lld ", v);
		c--;
		l++;
	}
	if(l > r) exit(0);
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	cin >> l >> r;
	seg.init(n, a);
	dnc(0, n - 1);
	lint s = 0, e = 1e15;
	while(s != e){
		lint m = (s+e)/2;
		if(trial(m) >= l) e = m;
		else s = m + 1;
	}
	lint k = trial(s);
	printAndMove(k - l + 1, s);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=0; i<rect.size(); i++){
		if(step[i] < rect[i].r + rect[i].l + 1){
			pq.push(pi(1ll * (step[i] + 1) * rect[i].h, i));
		}
	}
	while(!pq.empty()){
		auto x = pq.top(); pq.pop();
		int i = x.second;
		lint cnt = get(rect[i].l, rect[i].r, step[i]) - get(rect[i].l, rect[i].r, step[i] - 1);
		printAndMove(cnt, x.first);
		step[i]++;
		if(step[i] < rect[i].r + rect[i].l + 1){
			pq.push(pi(1ll * (step[i] + 1) * rect[i].h, i));
		}
	}
}