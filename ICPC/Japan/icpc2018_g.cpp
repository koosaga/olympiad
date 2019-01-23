#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 100005;

struct bit{
	int tree[MAXN];
	void clear(){
		memset(tree, 0, sizeof(tree));
	}
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int n, a[MAXN], cl[MAXN], cr[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	lint ret = 0;
	for(int i=1; i<=n; i++){
		cl[i] = bit.query(MAXN - 1) - bit.query(a[i]);
		bit.add(a[i], 1);
	}
	bit.clear();
	for(int i=n; i; i--){
		cr[i] = bit.query(MAXN - 1) - bit.query(a[i]);
		bit.add(a[i], 1);
	}
	for(int i=1; i<=n; i++) ret += min(cl[i], cr[i]);
	cout << ret << endl;
}
