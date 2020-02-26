#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

struct bit{
	lint tree[MAXN];
	void add(int x, int v){
		for(int i=x; i<MAXN; i+=i&-i) tree[i] += v;
	}
	lint query(int x){
		lint ret = 0;
		for(int i=x; i; i-=i&-i) ret += tree[i];
		return ret;
	}
}bit1, bit2;

int n, q;
vector<pi> event[MAXN];
int a[MAXN];
pi qry[MAXN];
char buf[69];

int main(){
	int tq;
	scanf("%*d %d",&tq);
	vector<int> crd;
	while(tq--){
		int x, y;
		scanf("%s %d %d", buf,&x,&y);
		if(*buf == 'U'){
			if(a[x]) event[q].emplace_back(a[x], -1);
			a[x] = y;
			if(a[x]) event[q].emplace_back(a[x], +1);
			crd.push_back(a[x]);
		}
		else{
			qry[q++] = pi(y, x);
		}
	}
	crd.push_back(0);
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for(int i=0; i<q; i++){
		for(auto &j : event[i]){
			int pos = lower_bound(all(crd), j.first) - crd.begin();
			bit1.add(pos, j.second);
			bit2.add(pos, j.second * j.first);
		}
		int lopos = lower_bound(all(crd), qry[i].first) - crd.begin();
		lint tot1 = (bit1.query(MAXN - 1) - bit1.query(lopos - 1)) * qry[i].first + bit2.query(lopos - 1);
		if(tot1 >= 1ll * qry[i].first * qry[i].second) puts("TAK");
		else puts("NIE");
	}
}
