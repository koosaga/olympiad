#include "Annalib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

static lint adj[305][305];
static int maxv[5] = {61, 31 * 31, 21 * 21 * 21, 16 * 16 * 16 * 16, 13 * 13 * 13 * 13 * 13};

void Anna(int N, int M, int A[], int B[], long long C[], int Q, int S[], int T[], int K, int U[]) {
	memset(adj, 0x3f, sizeof(adj));
	for(int i=0; i<M; i++){
		adj[A[i]][B[i]] = C[i];
	}
	for(int i=0; i<K; i++){
		adj[A[U[i]]][B[U[i]]] = adj[304][304];
	}
	for(int i=0; i<N; i++){
		adj[i][i] = 0;
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<N; k++){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	auto cmp = [&](int p, int a, int b){
		lint da = adj[S[p]][A[U[a]]] + C[U[a]] + adj[B[U[a]]][T[p]];
		lint db = adj[S[p]][T[p]];
		if(b < K){
			db = adj[S[p]][A[U[b]]] + C[U[b]] + adj[B[U[b]]][T[p]];
		}
		return da - db;
	};
	vector<int> v[6];
	for(int i=0; i<Q; i++){
		v[0].push_back(i);
	}
	unsigned long long dap = 0;
	for(int i=1; i<=K; i++){
		dap *= maxv[i-1];
		int pos = 0;
		int val = 0;
		for(int j=0; j<i; j++){
			val *= v[j].size() + 1;
			int cnt = 0;
			for(auto &l : v[j]){
				if(cmp(l, j, i) < 0) cnt++;
			}
			val += cnt;
			vector<int> tmp;
			for(auto &l : v[j]){
				if(cmp(l, j, i) < 0) tmp.push_back(l);
				else v[i].push_back(l);
			}
			v[j] = tmp;
		}
		dap += val;
	}
	for(int i=0; i<64; i++){
		Tap((dap >> i) & 1);
	}
}
