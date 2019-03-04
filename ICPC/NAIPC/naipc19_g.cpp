#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using llf = long double;
using lint = long long;
const int MAXN = 222222;
const int MAXT = 530000;

vector<pi> padd[2 * MAXN]; // (x, +-1)
vector<pi> sqry[2 * MAXN]; // (l, r)

int n;
int rec[MAXN][4];
vector<int> vx, vy;

struct bit{
	int tree[MAXN];
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

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		for(int j=0; j<4; j++) scanf("%d",&rec[i][j]);
		vx.push_back(rec[i][0]);
		vx.push_back(rec[i][2]);
		vy.push_back(rec[i][1]);
		vy.push_back(rec[i][3]);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	auto loc = [&](vector<int> &v, int x){
		return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
	};
	for(int i=0; i<n; i++){
		rec[i][0] = loc(vx, rec[i][0]);
		rec[i][2] = loc(vx, rec[i][2]);
		rec[i][1] = loc(vy, rec[i][1]);
		rec[i][3] = loc(vy, rec[i][3]);
		padd[rec[i][0]].emplace_back(rec[i][1], +1);
		padd[rec[i][0]].emplace_back(rec[i][3], +1);
		padd[rec[i][2]+1].emplace_back(rec[i][1], -1);
		padd[rec[i][2]+1].emplace_back(rec[i][3], -1);
		sqry[rec[i][0]].emplace_back(rec[i][1], rec[i][3]);
		sqry[rec[i][2]].emplace_back(rec[i][1], rec[i][3]);
	}
	lint ret = 0;
	for(int i=0; i<MAXN; i++){
		for(auto &j : padd[i]){
			bit.add(j.first, j.second);
		}
		for(auto &j : sqry[i]){
			ret += bit.query(j.second) - bit.query(j.first - 1);
		}
	}
	puts(ret == 4 * n ? "0" : "1");
}

