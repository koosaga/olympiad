#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, lint> pi;
#define all(v) (v).begin(), (v).end()
#define sz(v) ((int)(v).size())
const int MAXN = 300005;

int n, q;
int a[MAXN];

lint DCF(lint x, lint y, lint L, lint s){
	lint ret = 
	s * (x*x + x + y*y + y) + 
	(s * (s - 1) / 2) * L * (2 * x + 2 + 2 * y) +
	2 * L * L * ((s - 1) * s * (2 * s - 1) / 6);
	ret /= 2;
	return ret;
}

const int B = 1000;

struct query{
	int l, r, idx;
	bool operator<(const query &q)const{
		if((l / B) != (q.l / B)) return l < q.l;
		if((l / B) % 2) return r > q.r;
		return r < q.r;
	}
}qr[MAXN];

int tNew;
int cnt[MAXN];
int mp[MAXN];
unordered_set<int> tracker;

void add(int x, int v){
	if(cnt[a[x]] > 0){
		mp[cnt[a[x]]]--;
		if(mp[cnt[a[x]]] == 0) tracker.erase(cnt[a[x]]);
		tNew--;
	}
	cnt[a[x]] += v;
	if(cnt[a[x]] > 0){
		mp[cnt[a[x]]]++;
		if(mp[cnt[a[x]]] == 1) tracker.insert(cnt[a[x]]);
		tNew++;
	}
}

lint dap[MAXN];

int main(){
	scanf("%d %d",&n,&q);
	for(int i = 1; i <= n; i++){
	//	a[i] = (int)sqrt(i);
		scanf("%d",&a[i]);
	}
	for(int i = 0; i < q; i++){
	//	qr[i].l = rand() % n + 1;
	//	qr[i].r = rand() % n + 1;
//		if(qr[i].l > qr[i].r) swap(qr[i].l, qr[i].r);
		scanf("%d %d",&qr[i].l,&qr[i].r);
		qr[i].idx = i;
	}
	sort(qr, qr + q);
	int l = 1, r = 0;
	for(int i = 0; i < q; i++){
		while(l > qr[i].l) add(--l, 1);
		while(r < qr[i].r) add(++r, 1);
		while(l < qr[i].l) add(l++, -1);
		while(r > qr[i].r) add(r--, -1);
		int N = qr[i].r - qr[i].l + 1;
		lint ret = 1ll * N * (N + 1) / 2 * tNew;
		int L = 0, R = 0;
		vector<pi> v;
		for(auto &i : tracker){
			v.emplace_back(i, mp[i]);
		}
		sort(all(v));
		for(auto &[i, j] : v){
			int ost = (j + 1) / 2;
			int est = j / 2;
			ret -= DCF(L, N - L - ost * i, i, ost);
			L += ost * i;
			ret -= DCF(R, N - R - est * i, i, est);
			R += est * i;
			if(j & 1) swap(L, R);
		}
		dap[qr[i].idx] = ret;
	}
	for(int i = 0; i < q; i++) printf("%lld\n", dap[i]);
}


