#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2000005;
using lint = long long;
const int W = 13;

int w, h, k;
vector<int> gph[1 << W];
bool vis[51][1 << W];
vector<int> ascend(vector<int> v, int x){
	if(x == 0) return v;
	memset(vis, 0, sizeof(vis));
	queue<pi> que;
	for(int i = 0; i < sz(v); i++){
		if(v[i]){
			vis[0][i] = 1;
			que.emplace(0, i);
		}
	}
	while(sz(que)){
		auto x = que.front(); que.pop();
		if(x.first == 50) break;
		for(auto &y : gph[x.second]){
			if(!vis[x.first + 1][y]){
				vis[x.first + 1][y] = 1;
				que.emplace(x.first + 1, y);
			}
		}
	}
	if(x > 40){
		int delta = (x - 40) / 6;
		x -= delta * 6;
	}
	vector<int> ret;
	for(int i = 0; i < (1<<w); i++){
		ret.push_back(vis[x][i]);
	}
	return ret;
}

int main(){
	scanf("%d %d %d",&w,&h,&k);
	for(int i = 0; i < (1<<w); i++){
		int nxt[14][1 << W] = {};
		nxt[0][0] = 1;
		for(int j = 0; j < w; j++){
			for(int k = 0; k < (1<<w); k++){
				if(!nxt[j][k]) continue;
				if((i >> j) & 1) nxt[j + 1][k] = 1;
				else{
					if(j > 0 && (k & (3 << (j - 1))) == 0) nxt[j + 1][k | (3 << (j-1))] = 1;
					if(j + 1 < w && (k & (3 << j)) == 0) nxt[j + 1][k | (3 << j)] = 1;
					if(j + 1 < w && (i >> (j + 1)) % 2 == 0 && (k >> j) % 2 == 0){
						nxt[j + 2][k | (1 << j)] = 1;
					}
					if(j + 1 < w && (i >> (j + 1)) % 2 == 0 && (k >> (j + 1)) % 2 == 0){
						nxt[j + 2][k | (1 << (j + 1))] = 1;
					}
				}
			}
		}
		for(int j = 0; j < (1<<w); j++){
			if(nxt[w][j]){
				gph[i].push_back(j);
			}
		}
	}
	map<int, int> mp;
	for(int i = 0; i < k; i++){
		int x, y; scanf("%d %d",&x,&y);
		mp[y] |= (1 << (x - 1));
	}
	mp[h + 1] = 0;
	vector<int> cur(1 << w);
	cur[(1<<w) - 1] = 1;
	int curY = 0;
	for(auto &[y, x] : mp){
		cur = ascend(cur, y - 1 - curY);
		vector<int> nxt(1 << w);
		for(int z = 0; z < (1 << w); z++){
			if(cur[z]){
				for(auto &p : gph[z]){
					if((p & x) == 0) nxt[p | x] = 1;
				}
			}
		}
		cur = nxt;
		curY = y;
	}
	puts(cur[0] ? "YES" : "NO");
}
