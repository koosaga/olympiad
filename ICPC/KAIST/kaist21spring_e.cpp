#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 10;

struct node{
	int x, y, d;
};

queue<node> que;

int n, k, m, c[MAXN];
int dist[1 << MAXN][1 << MAXN];
int equip[1 << MAXN];

void enq(int x, int y, int d){
	if(dist[x][y] > d){
		dist[x][y] = d;
		que.push({x, y, d});
	}
}

int main(){
	cin >> n >> k >> m;
	int st = 0;
	for(int i = 0; i < n; i++){
		cin >> c[i];
		if(c[i] == 1) st |= (1 << i);
	}
	for(int i = 0; i < m; i++){
		int q; cin >> q;
		while(q--){
			int idx; cin >> idx; idx--;
			equip[1 << i] |= (1 << idx);
		}
	}
	for(int i = 1; i < (1<<m); i++){
		int j = i & -i;
		if(i != j) equip[i] = (equip[j] | equip[i ^ j]);
	}
	memset(dist, 0x3f, sizeof(dist));
	enq(0, st, 0);
	while(sz(que)){
		auto x = que.front(); que.pop();
		for(int i = 0; i < m; i++){
			enq(x.x ^ (1 << i), x.y, x.d + 1);
		}
		for(int i = 1; i <= k; i++){
			int cur = x.y;
			for(int j = 0; j < n; j++){
				if((equip[x.x] >> j) & 1) continue;
				if(c[j] == i) cur |= (1<<j);
				else cur &= (~(1<<j));
			}
			enq(x.x, cur, x.d + 1);
		}
	}
	int ret = dist[0][(1<<n)-1];
	if(ret > 1e7) ret = -1;
	cout << ret << endl;
}
