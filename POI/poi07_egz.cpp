#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

vector<pi> v[2];
int n, m, k, p, d1[MAXN], d2[MAXN];
int l[MAXN], r[MAXN];

int solve(int k){
	int ptr = 0;
	int ans = 0;
	for(int i=n-1; i>=0; i--){
		while(ptr < n-1 && r[ptr+1] + l[i] <= k){
			ptr++;
		}
		if(l[i] + r[ptr] <= k) ans = max(ans, i + ptr - n + 2);
	}
	return ans;
}

struct seg{
	int tree[MAXN];
	void init(){
		memset(tree, 0, sizeof(tree));
	}
	void add(int x, int v){
		while(x <= n){
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
}seg;

int main(){
	scanf("%d %d %d %d",&n,&m,&p,&k);
	for(int i=0; i<p; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		if(z == 1) v[z].push_back(pi(m-y, x));
		else v[z].push_back(pi(m-y, n-x));
	}
	memset(l, 0x3f, sizeof(l));
	memset(r, 0x3f, sizeof(r));
	sort(v[0].begin(), v[0].end());
	sort(v[1].begin(), v[1].end());
	seg.init();
	for(int i=0; i<v[0].size(); i++){
		d1[i] = seg.query(v[0][i].second - 1) + 1;
		seg.add(v[0][i].second, d1[i]);
		l[v[0][i].second] = min(l[v[0][i].second], v[0][i].second - d1[i]);
	}
	seg.init();
	for(int i=0; i<v[1].size(); i++){
		d2[i] = seg.query(v[1][i].second - 1) + 1;
		seg.add(v[1][i].second, d2[i]);
		r[v[1][i].second] = min(r[v[1][i].second], v[1][i].second - d2[i]);
	}
	l[0] = r[0] = 0;
	for(int i=1; i<n; i++) l[i] = min(l[i], 1 + l[i-1]), r[i] = min(r[i], 1 + r[i-1]);
	cout << solve(k) - solve(0) << endl;
}

