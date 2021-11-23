#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1000005;

vector<int> comp(vector<int> v){
	vector<int> w = v;
	sort(all(w));
	w.resize(unique(all(w)) - w.begin());
	for(auto &x : v) x = lower_bound(all(w), x) - w.begin() + 1;
	return v;
}

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i = x; i < MAXN; i += i & -i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i = x; i; i -= i & -i) ret += tree[i];
		return ret;
	}
}bit;

void addVal(int x, int v){
	bit.add(x, v);
}

pi getRank(int x){
	return pi(bit.query(x - 1), bit.query(x));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++) cin >> b[i];
	a = comp(a); b = comp(b);
	vector<pi> rk(n);
	for(int i = 0; i < n; i++){
		rk[i] = getRank(a[i]);
		addVal(a[i], +1);
	}
	for(int i = 0; i < n; i++) addVal(a[i], -1);
	vector<int> fail(n + 1);
	int p = 0;
	for(int i = 1; i < n; i++){
		while(p && getRank(a[i]) != rk[p]){
			for(int j = p; j > fail[p]; j--){
				addVal(a[i - j], -1);
			}
			p = fail[p];
		}
		if(getRank(a[i]) == rk[p]){
			addVal(a[i], +1);
			p++;
		}
		fail[i + 1] = p;
	}
	for(int j = p; j; j--) addVal(a[n - j], -1);
	p = 0;
	vector<int> ans;
	for(int i = 0; i < m; i++){
		while(p && getRank(b[i]) != rk[p]){
			for(int j = p; j > fail[p]; j--){
				addVal(b[i - j], -1);
			}
			p = fail[p];
		}
		if(getRank(b[i]) == rk[p]){
			addVal(b[i], +1);
			p++;
		}
		if(p == n){
			ans.push_back(i - n + 2);
			for(int j = p; j > fail[p]; j--){
				addVal(b[i - j + 1], -1);
			}
			p = fail[p];
		}
	}
	if(sz(ans) == 0) ans.push_back(0);
	for(auto &i : ans) cout << i << ' ';
}
