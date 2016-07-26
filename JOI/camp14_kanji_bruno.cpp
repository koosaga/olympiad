#include "Brunolib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

static lint adj[305][305];
static int opt[305][305];
static int num[305][305];

static void trace(int s, int e){
	if(s == e) return;
	int o = opt[s][e];
	if(o != -1){
		trace(s, o); trace(o, e);
	}
	else Answer(num[s][e]);
}

static int maxv[5] = {61, 31 * 31, 21 * 21 * 21, 16 * 16 * 16 * 16, 13 * 13 * 13 * 13 * 13};

void Bruno(int N, int M, int A[], int B[], long long C[], int Q, int S[], int T[], int K, int U[], int L, int X[]) {
	int p = 0;
	memset(adj, 0x3f, sizeof(adj));
	memset(opt, -1, sizeof(opt));
	memset(num, -1, sizeof(num));
	for(int i=0; i<M; i++){
		if(C[i] == -1) continue;
		num[A[i]][B[i]] = i;
		adj[A[i]][B[i]] = C[i];
	}
	for(int i=0; i<N; i++){
		adj[i][i] = 0;
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<N; k++){
				if(adj[j][k] > adj[j][i] + adj[i][k]){
					adj[j][k] = adj[j][i] + adj[i][k];
					opt[j][k] = i;
				}
			}
		}
	}
	auto cmp = [&](int p, int a, int b){
		lint da = adj[S[p]][A[U[a]]] + adj[B[U[a]]][T[p]];
		lint db = adj[S[p]][T[p]];
		if(b < K){
			db = adj[S[p]][A[U[b]]] + adj[B[U[b]]][T[p]];
		}
		return da - db;
	};
	unsigned long long dap = 0;
	for(int i=0; i<64; i++){
		if(X[i]) dap |= (1ull << i);
	}
	int val[6] = {};
	for(int i=K; i; i--){
		val[i] = dap % maxv[i-1];
		dap /= maxv[i-1];
	}
	vector<int> v[6];
	for(int i=0; i<Q; i++){
		v[0].push_back(i);
	}
	for(int i=1; i<=K; i++){
		for(int j=i-1; j>=0; j--){
			int cnt = val[i] % (v[j].size() + 1);
			val[i] /= v[j].size() + 1;
			vector<pi> dtmp;
			for(auto &l : v[j]){
				dtmp.push_back({cmp(l, j, i), l});
			}
			sort(dtmp.begin(), dtmp.end());
			v[j].clear();
			for(int k=0; k<cnt; k++){
				v[j].push_back(dtmp[k].second);
			}
			for(int k=cnt; k<dtmp.size(); k++){
				v[i].push_back(dtmp[k].second);
			}
		}
	}
	int pos[60];
	for(int i=0; i<=K; i++){
		for(auto &j : v[i]){
			pos[j] = i;
		}
	}
	for(int i=0; i<Q; i++){
		if(pos[i] == K){
			trace(S[i], T[i]);
		}
		else{
			trace(S[i], A[U[pos[i]]]);
			Answer(U[pos[i]]);
			trace(B[U[pos[i]]], T[i]);
		}
		Answer(-1);
	}
}
