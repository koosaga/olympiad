// Ivan Carvalho
// Solution to https://dmoj.ca/problem/joi14p6
#include <bits/stdc++.h>
#include "secret.h"
using namespace std;
const int MAXN = 1010;
int V[MAXN],P[MAXN][MAXN],n;
void precalc(int l,int r){
	if(l == r){
		P[l][l] = V[l];
		return;
	}
	int m = (l+r)/2;
	precalc(l,m);
	precalc(m+1,r);
	for(int i = m;i>=l;i--){
		if(P[i][m] == -1){
			P[i][m] = Secret(V[i],P[i+1][m]);
		}
	}
	for(int i = m + 1;i<=r;i++){
		if(P[m+1][i] == -1){
			P[m+1][i] = Secret(P[m+1][i-1],V[i]);
		}
	}
}
void Init(int N,int A[]){
	n = N;
	for(int i = 1;i<=n;i++){
		V[i] = A[i-1];
	}
	memset(P,-1,sizeof(P));
	precalc(1,n);
}
int Query(int L,int R){
	L++;
	R++;
	for(int i = L;i+1<=R;i++){
		if(P[L][i] != -1 && P[i+1][R] != -1){
			return Secret(P[L][i],P[i+1][R]);
		}
	}
	return P[L][R];
}