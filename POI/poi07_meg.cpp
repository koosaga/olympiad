#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 250005;

int n;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x <= n){
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

vector<int> gph[MAXN];
int din[MAXN], dout[MAXN], dep[MAXN], piv;

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

char buf[5];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	int q; scanf("%d",&q);
	q += n - 1;
	for(int i=0; i<q; i++){
		scanf("%s", buf);
		if(*buf == 'W'){
			int x;
			scanf("%d",&x);
			printf("%d\n", dep[x] - bit.query(din[x]));
		}
		else{
			int x, y;
			scanf("%d %d",&x,&y);
			if(dep[x] > dep[y]) swap(x, y);
			bit.add(din[y], 1);
			bit.add(dout[y] + 1, -1);
		}
	}
}

