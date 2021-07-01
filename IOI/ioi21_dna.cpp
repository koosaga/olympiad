#include "dna.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

int sum[MAXN][3][3];

void init(std::string a, std::string b) {
	auto sgn = [&](char c){
		switch(c){
			case 'A':{
				return 0;
			}
			case 'C':{
				return 1;
			}
			default:{
				return 2;
			}
		}
	};
	for(int i = 0; i < sz(a); i++){
		sum[i + 1][sgn(a[i])][sgn(b[i])]++;
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				sum[i+1][j][k] += sum[i][j][k];
			}
		}
	}
}

int get_distance(int x, int y) {
	int adj[3][3] = {};
	int src[3] = {};
	int snk[3] = {};
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			adj[i][j] = sum[y+1][i][j] - sum[x][i][j];
			src[i] += adj[i][j];
			snk[j] += adj[i][j];
		}
	}
	for(int i = 0; i < 3; i++){
		if(src[i] != snk[i]) return -1;
	}
	int ret = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < i; j++){
			int d = min(adj[i][j], adj[j][i]);
			adj[i][j] -= d;
			adj[j][i] -= d;
			ret += d;
		}
	}
	int d1 = max(adj[0][1], adj[1][0]);
	int d2 = max(adj[0][2], adj[2][0]);
	int d3 = max(adj[1][2], adj[2][1]);
	assert(d1 == d2 && d2 == d3);
	ret += 2 * d1;
	return ret;
}
