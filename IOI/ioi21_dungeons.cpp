#include "dungeons.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 400005;

int n;
vector<int> s, p, w, l;
int nxt[8][24][MAXN];
int cost[8][24][MAXN];
int value[8][24][MAXN];
lint dp[MAXN];

void init(int _n, std::vector<int> _s, std::vector<int> _p, std::vector<int> _w, std::vector<int> _l) {
	tie(n, s, p, w, l) = make_tuple(_n, _s, _p, _w, _l);
	s.resize(n + 1);
	for(int i = n - 1; i >= 0; i--) dp[i] = dp[w[i]] + s[i];
	for(int i = 0; i < 8; i++){
		int L = (1 << (3*i));
		for(int j = 0; j < n; j++){
			if(s[j] < L){
				nxt[i][0][j] = w[j];
				cost[i][0][j] = s[j];
				value[i][0][j] = 1e9;
			}
			else{
				nxt[i][0][j] = l[j];
				cost[i][0][j] = p[j];
				value[i][0][j] = s[j];
			}
		}
		nxt[i][0][n] = n;
		cost[i][0][n] = 1e8;
		value[i][0][n] = 1e9;
		for(int j = 1; j < 3*i+3; j++){
			for(int k = 0; k <= n; k++){
				nxt[i][j][k] = nxt[i][j-1][nxt[i][j-1][k]];
				cost[i][j][k] = cost[i][j-1][k] + cost[i][j-1][nxt[i][j-1][k]];
				cost[i][j][k] = min(cost[i][j][k], int(1e9));
				value[i][j][k] = min(value[i][j-1][k], value[i][j-1][nxt[i][j-1][k]] - cost[i][j-1][k]);
				value[i][j][k] = max(value[i][j][k], 0);
			}
		}
	}
	return;
}

long long simulate(int x, int zz) {
	lint z = zz;
	for(int i = 0; i < 8; i++){
		while(z < (1 << (3*i+3))){
			for(int j = 3*i+2; j >= 0; j--){
				if(nxt[i][j][x] != n && z + cost[i][j][x] < (1<<(3*i+3)) && value[i][j][x] > z){
					z += cost[i][j][x];
					x = nxt[i][j][x];
				}
			}
			if(x != n && z < (1 << (3*i+3)) && (s[x] > z || s[x] < (1 << (2*i)))){
				z += cost[i][0][x];
				x = nxt[i][0][x];
			}
			if(x == n){
				break;
			}
			if(s[x] <= z){
				z += s[x];
				x = w[x];
			}
			if(x == n) break;
		}
	}
	return z + dp[x];
}


