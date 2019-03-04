#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

struct seg{
	int tree[270000];
	int lazy[270000];
	void init(int s, int e, int p){
		tree[p] = lazy[p] = 0;
		if(s == e) return;
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			lazy[p] += v;
			if(lazy[p] == 0) tree[p] = (ps == pe ? 0 : (tree[2*p] + tree[2*p+1]));
			else tree[p] = (pe - ps + 1);
			return;
		}
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		if(lazy[p] == 0) tree[p] = tree[2*p] + tree[2*p+1];
		else tree[p] = (pe - ps + 1);
	}
}seg;

int n, m, k;
int che[MAXN], a[MAXN];
vector<int> v[MAXN];
set<int> s[MAXN];

vector<int> divisor(int x){
	vector<int> v;
	while(x > 1){
		int l = che[x];
		while(x % l == 0) x /= l;
		v.push_back(l);
	}
	return v;
}

void Do(int s, int e, int x){
	if(e - s >= k) return;
	int ns = e - k + 1;
	int ne = s;
	ns = max(ns, 1);
	ne = min(ne, n - k + 1);
	if(ns <= ne) seg.add(ns, ne, 1, n-k+1, 1, x);
}

int main(){
	for(int i=2; i<=100000; i++){
		for(int j=i; j<=100000; j+=i){
			if(!che[j]) che[j] = i;
		}
	}
	while(true){
		scanf("%d %d %d",&n,&k,&m);
		if(n == 0) break;
		seg.init(1, n-k+1, 1);
		for(int i=1; i<=n; i++) scanf("%d",&a[i]), v[i] = divisor(a[i]);
		set<int> occur;
		for(int i=1; i<=n; i++){
			for(auto &j : v[i]){
				s[j].insert(i);
				occur.insert(j);
			}
		}
		for(auto &i : occur){
			auto it = s[i].begin();
			for(auto &j : s[i]){
				if(*s[i].begin() == j) continue;
				Do(*it, j, 1);
				it++;
			}
		}
		printf("%d\n", seg.tree[1]);
		for(int i=1; i<=m; i++){
			int x, w;
			scanf("%d %d",&x,&w);
			for(auto &j : v[x]){
				auto l = s[j].find(x);
				int vl = -1, vr = -1;
				if(l != s[j].begin()){
					auto pl = l;
					pl--;
					Do(*pl, *l, -1);
					vl = *pl;
				}
				if(l != s[j].end()){
					auto pr = l;
					pr++;
					if(pr != s[j].end()) Do(*l, *pr, -1), vr = *pr;
				}
				s[j].erase(l);
				if(s[j].empty()) occur.erase(j);
				if(vl != -1 && vr != -1) Do(vl, vr, 1);
			}
			a[x] = w;
			v[x] = divisor(w);
			for(auto &j : v[x]){
				occur.insert(j);
				s[j].insert(x);
				auto l = s[j].find(x);
				int vl = -1, vr = -1;
				if(l != s[j].begin()){
					auto pl = l;
					pl--;
					Do(*pl, *l, 1);
					vl = *pl;
				}
				if(l != s[j].end()){
					auto pr = l;
					pr++;
					if(pr != s[j].end()) Do(*l, *pr, 1), vr = *pr;
				}
				if(vl != -1 && vr != -1) Do(vl, vr, -1);
			}
			printf("%d\n", seg.tree[1]);
		}
	    for(auto &i : occur) s[i].clear();
		printf("%lld\n", accumulate(a+1, a+n+1, 0ll));
	}
}
