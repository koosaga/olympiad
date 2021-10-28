#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int MAXT = 1000005;

struct bit{
	int tree[MAXT];
	void add(int x, int v){
		for(int i = x; i < MAXT; i += i & -i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i = x; i; i -= i & -i) ret += tree[i];
		return ret;
	}
}bit;

int n;
pi a[MAXN], b[MAXN];

int main(){
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		scanf("%d",&a[i].first);
		a[i].first++;
	}
	for(int i = 0; i < n; i++){
		scanf("%d",&a[i].second);
		a[i].second++;
	}
	sort(a, a + n);
	vector<int> lo(n), hi(n);
	for(int i = 0; i < n; ){
		int j = i;
		while(j < n && a[i].first == a[j].first) j++;
		for(int k = i; k < j; k++){
			lo[k] = bit.query(a[k].second - 1);
		}
		for(int k = i; k < j; k++){
			bit.add(a[k].second, +1);
		}
		i = j;
	}
	memset(bit.tree, 0, sizeof(bit.tree));
	reverse(a, a + n);
	for(int i = 0; i < n; i++) a[i].second = 1000002 - a[i].second;
	for(int i = 0; i < n; ){
		int j = i;
		while(j < n && a[i].first == a[j].first) j++;
		for(int k = i; k < j; k++){
			hi[n-1-k] = bit.query(a[k].second - 1);
		}
		for(int k = i; k < j; k++){
			bit.add(a[k].second, +1);
		}
		i = j;
	}
	lint ret = 0;
	for(int i = 0; i < n; i++) ret += 1ll * lo[i] * hi[i];
	cout << ret << endl;
}
