#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 200005;
const int mod = 1e9 + 7;

struct bit{
	int tree[MAXN];
	void upd(int x, int v){
		while(x < MAXN){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
}bit;

int n, x, a[MAXN], dl[MAXN], dr[MAXN];
vector<int> v;

int main(){
	scanf("%d %d",&n,&x);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	vector<int> l;
	for(int i=1; i<=n; i++){
		auto it = lower_bound(l.begin(), l.end(), a[i]);
		dl[i] = it - l.begin() + 1;
		if(it == l.end()) l.push_back(a[i]);
		else *it = a[i];
	}
	l.clear();
	for(int i=n; i; i--){
		auto it = lower_bound(l.begin(), l.end(), -a[i]);
		dr[i] = it - l.begin() + 1;
		if(it == l.end()) l.push_back(-a[i]);
		else *it = -a[i];
	}
	int ans = l.size();
	for(int i=1; i<=n; i++){
		auto l = lower_bound(v.begin(), v.end(), a[i] + x) - v.begin();
		ans = max(ans, dr[i] + bit.query(l));
		bit.upd(lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1, dl[i]);
	}
	cout << ans << endl;
}
