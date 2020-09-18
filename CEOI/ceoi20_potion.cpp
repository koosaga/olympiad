#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 400005;
const int MAXT = 270000;
const int mod = 1e9 + 7;

int n, m, q;

set<int> gph[MAXN];
pi a[MAXN], FUCK[MAXN], fucking[MAXN];
int rev[MAXN];

bitset<MAXN> time_line[205];
bitset<MAXN> mark;

int main(){
	scanf("%d %*d %d %d",&n,&m,&q);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i].first);
		a[i].second = i;
	}
	sort(a, a + n);
	vector<pi> crd;
	for(int i=0; i<n; i++) rev[a[i].second] = i;
	for(int i=1; i<=m; i++){
		int s, e; scanf("%d %d",&s,&e);
		s = rev[s]; e = rev[e];
		FUCK[i] = pi(s, e);
		crd.emplace_back(s, e);
		crd.emplace_back(e, s);
	}
	time_line[0][0] = 1;
	mark[0] = 1;
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for(int i=1; i<=m; i++){
		int s, e; tie(s, e) = FUCK[i];
		int x = lower_bound(all(crd), pi(s, e)) - crd.begin() + 1;
		int y = lower_bound(all(crd), pi(e, s)) - crd.begin() + 1;
		fucking[i] = pi(x, y);
		mark.flip(x);
		mark.flip(y);
		if(i % 1000 == 0) time_line[i / 1000] = mark;
	}
	bitset<MAXN> fuck;
	auto Get = [&](vector<int> &ret, int pos, int t){
		int x = lower_bound(all(crd), pi(pos, -1)) - crd.begin() + 1;
		int y = lower_bound(all(crd), pi(pos + 1, -1)) - crd.begin() + 1;
		int qq = fuck._Find_next(x - 1);
		while(qq < y){
			ret.push_back(crd[qq - 1].second);
			qq = fuck._Find_next(qq);
		}
	};
	while(q--){
		int x, y, d; scanf("%d %d %d",&x,&y,&d);
		x = rev[x];
		y = rev[y];
		vector<int> res1;
		vector<int> res2;
		fuck = time_line[d / 1000];
		for(int i=(d/1000)*1000+1; i<=d; i++){
			fuck.flip(fucking[i].first);
			fuck.flip(fucking[i].second);
		}
		Get(res1, x, d);
		Get(res2, y, d);
		int ret = 1e9;
		int ptr = 0;
		for(auto &i : res1){
			while(ptr < sz(res2) && a[res2[ptr]].first <= a[i].first){
				ptr++;
			}
			for(int j=ptr-1; j<ptr+1; j++){
				if(j < 0 || j >= sz(res2)) continue;
				ret = min(ret, abs(a[i].first - a[res2[j]].first));
			}
		}
		printf("%d\n", ret);
		fflush(stdout);
	}
}

