#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

vector<pi> v;
vector<int> gph[200005];
int n, d, dep[200005], par[200005], val[200005];
int din[200005], dout[200005], piv;

struct seg{
	int tree[530000], lim;
	void init(){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	int query(int x){
		x += lim;
		int ret = 1e9;
		while(x){
			ret = min(ret, tree[x]);
			x >>= 1;
		}
		return ret;
	}
	void update(int s, int e, int x){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) tree[s] = min(tree[s], x);
			if(e%2 == 0) tree[e] = min(tree[e], x);
			s = (s+1)/2;
			e = (e-1)/2;
		}
		if(s == e) tree[s] = min(tree[s], x);
	}
}seg;

void dfs(int x){
	din[x] = piv++;
	for(auto &i : gph[x]) dfs(i);
	dout[x] = piv;
}

int main(){
	memset(val, 0x3f, sizeof(val));
	scanf("%d %d",&n,&d);
	v.push_back(pi(0, 0));
	par[0] = -1;
	for(int i=1; i<n; i++){
		scanf("%d",&par[i]);
		gph[par[i]].push_back(i);
		dep[i] = dep[par[i]] + 1;
		v.push_back(pi(dep[i], i));
	}
	dfs(0);
	seg.init();
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	int cnt = 0;
	for(auto &i : v){
		if(seg.query(din[i.second]) <= d - 1 - dep[i.second]) continue;
		for(int j=i.second; j!=-1; j=par[j]){
			seg.update(din[j], dout[j]-1, dep[i.second] - 2 * dep[j]);
		}
		cnt++;
	}
	cout << cnt << endl;
}
