#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200005;

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
	int kth(int x){
		int pos = 0;
		for(int i = 17; i >= 0; i--){
			if(pos + (1<<i) < MAXN && tree[pos + (1<<i)] < x){
				pos += (1<<i);
				x -= tree[pos];
			}
		}
		return pos + 1;
	}
}bit;

int main(){
	int n, q; cin >> n >> q;
	vector<int> a(n);
	vector<int> rev(n + 1);
	vector<vector<pi>> v(n + 1);
	for(int i = 0; i < n; i++) cin >> a[i], rev[a[i]] = i;
	vector<int> ans(q);
	for(int i = 0; i < q; i++){
		int t, x; cin >> t >> x;
		t = min(t, n);
		if(t == 0) ans[i] = a[x - 1];
		else v[t].emplace_back(x - 1, i);
	}
	vector<int> nxt(n);
	vector<int> ds(n + 1);
	auto SetVal = [&](int x, int v){
		bit.add(x, v - ds[x]);
		ds[x] = v;
	};
	for(int i = 0; i < n; ){
		int j = i + 1;
		while(j < n && a[j] < a[i]) j++;
		SetVal(a[i], j - i);
		i = j;
	}
	{
		vector<int> v;
		for(int i = n - 1; i >= 0; i--){
			while(sz(v) && a[v.back()] < a[i]) v.pop_back();
			if(sz(v)) nxt[i] = v.back();
			else nxt[i] = n;
			v.push_back(i);
		}
	}
	for(int i = 1; i <= n; i++){
		int itf = bit.kth(n / 2 + 1);
		int its = ds[itf];
		int sum = bit.query(itf - 1);
		if(sum < n / 2){
			int l = rev[itf];
			int r = l + its;
			SetVal(a[l], n / 2 - sum);
			l += n / 2 - sum;
			for(int i = l; i < r; i = nxt[i]){
				SetVal(a[i], min(r, nxt[i]) - i);
			}
		}
		for(auto [pos, idx] : v[i]){
			int qos = bit.kth(pos + 1);
			int sum = bit.query(qos - 1);
			ans[idx] = a[rev[qos] + pos - sum];
		}
	}
	for(auto &x : ans) cout << x << "\n";
}
