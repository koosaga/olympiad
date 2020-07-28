// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco10p1
#include <bits/stdc++.h>
#define NOTHING 0
#define WAITS 1
#define BARKS 2
using namespace std;
const int MAXN = 2010;
vector<int> grafo[MAXN];
int estado[MAXN/2][MAXN],dogs,tempo,W[MAXN/2],T,F;
void dfs(int x){
	if(estado[x][tempo] == WAITS || estado[x][tempo] == BARKS) return;
	for(int v : grafo[x]){
		if(estado[v][tempo] == WAITS || estado[v][tempo] == NOTHING) continue;
		for(int i = tempo + 1;i <= tempo + W[x] - 1;i++) estado[x][i] = WAITS;
		estado[x][tempo+W[x]] = BARKS;
		return;
	}
}
int main(){
	cin >> dogs;
	for(int i = 1;i<=dogs;i++) cin >> W[i];
	cin >> F;
	while(F--){
		int i,j;
		cin >> i >> j;
		grafo[j].push_back(i);
	}
	estado[1][0] = BARKS;
	cin >> T;
	for(tempo = 0;tempo<=T;tempo++){
		for(int i = 1;i<=dogs;i++){
			dfs(i);
		}
	}
	for(int i = 1;i<=dogs;i++){
		int resp = 0;
		for(tempo = 0;tempo <= T;tempo++){
			if(estado[i][tempo] == BARKS) resp++;
		}
		cout << resp << endl;
	}
	return 0;
}