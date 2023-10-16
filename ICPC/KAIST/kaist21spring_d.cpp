#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

struct bit{
	vector<int> tree;
	void init(int n){
		tree.clear();
		tree.resize(n + 5);
	}
	void add(int x, int v){
		for(int i = x + 2; i < sz(tree); i += i & -i) tree[i] += v;
	}
	int query(int x){
		x = max(x + 2, 0);
		int ret = 0;
		for(int i = x; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int kth(int x){
		int pos = 0;
		for(int i = 24; i >= 0; i--){
			if(pos + (1<<i) < sz(tree) && tree[pos + (1<<i)] < x){
				pos += (1<<i);
				x -= tree[pos];
			}
		}
		return pos - 1;
	}
}bit;

int main(){
	int n; lint k;
	scanf("%d %lld",&n,&k);
	vector<lint> a(n + 1);
	for(int i = 1; i <= n; i++){
		scanf("%lld",&a[i]);
		a[i] += a[i-1];
	}
	int j = 0;
	vector<int> r(n + 1), f(n + 1);
	vector<vector<int>> v(n + 1);
	for(int i = 0; i <= n; i++){
		while(j+1 <= n && a[j+1] - a[i] <= k) j++;
		r[i] = j - i;
	}
	j = 0;
	for(int i = 0; i <= n; i++){
		while(a[i] - a[j] > k) j++;
		f[i] = min(r[i], i - j);
		v[i + f[i]].push_back(i);
	}
	int ret = 0;
	bit.init(n);
	for(int i = n; i >= 0; i--){
		for(auto &j : v[i]){
			bit.add(j, 1);
		}
		int lo = bit.query(i - r[i] - 1);
		ret = max(ret, i - bit.kth(lo + 1));
	}
	cout << ret << endl;
}