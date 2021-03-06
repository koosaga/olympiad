#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i = x; i < MAXN; i += i & -i){
			tree[i] += v;
		}
	}
	int query(int x){
		int ret = 0;
		for(int i = x; i; i -= i & -i) ret += tree[i];
		return ret;
	}
}bit;

int n, q, a[MAXN], ret[MAXN];		
vector<pi> qr[MAXN];

int main(){
	scanf("%d %d",&n,&q);
	vector<int> stk;
	vector<pi> v;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		while(sz(stk) && a[stk.back()] > a[i]) stk.pop_back();
		if(sz(stk) && a[stk.back()] == a[i]){
			v.emplace_back(stk.back(), i);
		}
		stk.push_back(i);
	}
	for(int i=0; i<q; i++){
		int s, e; scanf("%d %d",&s,&e);
		qr[s].emplace_back(e, i);
		ret[i] = e - s + 1;
	}
	sort(all(v));
	for(int i = n; i; i--){
		while(sz(v) && v.back().first == i){
			bit.add(v.back().second, 1);
			v.pop_back();
		}
		for(auto &[e, idx] : qr[i]){
			ret[idx] -= bit.query(e);
		}
	}
	for(int i=0; i<q; i++){
		printf("%d\n", ret[i]);
	}
}
