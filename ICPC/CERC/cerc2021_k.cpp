#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;
const int mod = 998244353; //1e9 + 7;//998244353;

struct bit{
	lint tree[MAXN];
	void add(int x, int v){
		for(int i = x; i < MAXN; i += i & -i) tree[i] += v;
	}
	lint query(int x){
		lint ret = 0;
		for(int i = x; i; i -= i & -i) ret += tree[i];
		return ret;
	}
}bit;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<lint> a(n);
	for(int i = 1; i < n; i++){
		cin >> a[i];
		bit.add(i, a[i]);
	}
	auto solve = [&](){
		int s = 0, e = n - 1;
		while(s != e){
			int m = (s + e + 1) / 2;
			if(bit.query(m) < bit.query(n - 1) - bit.query(m)) s = m;
			else e = m - 1;
		}
		lint l = max(bit.query(s), bit.query(n - 1) - bit.query(s));
		lint r = max(bit.query(s+1), bit.query(n - 1) - bit.query(s+1));
		return - bit.query(n - 1) + 2 * min(l, r);
	};
	cout << solve() << "\n";
	int q; cin >> q;
	for(int i = 0; i < q; i++){
		int x, v; cin >> x >> v;
		bit.add(x, v - a[x]);
		a[x] = v;
		cout << solve() << "\n";
	}
}
