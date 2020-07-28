// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi14p3
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1510;

static int pai[MAXN],grau[MAXN][MAXN],N;

int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}

void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(x > y) swap(x,y);
	pai[y] = x;
	for(int i = 0;i<N;i++){
		if(find(i) != i) continue;
		grau[x][i] += grau[y][i];
		grau[i][x] += grau[i][y];
		grau[y][i] = 0;
		grau[i][y] = 0;
	}
}

void initialize(int n){

	for(int i = 0;i<n;i++){
		pai[i] = i;
		for(int j = 0;j<n;j++) grau[i][j] = 1;
		grau[i][i] = 0;
	}
	N = n;

}

int hasEdge(int u, int v) {
    int x = find(u),y = find(v);
    if(x == y){
    	return 0;
    }
    grau[x][y]--;
    grau[y][x]--;
    if(grau[x][y] == 0){
    	join(x,y);
    	return 1;
    }
    else{
    	return 0;
    }
}

