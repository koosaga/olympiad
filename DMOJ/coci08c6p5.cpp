// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c6p5
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
const int MAXN = 2001;
const int MAXM = 201;
vector<ii> grafo[2*MAXN];
int tab[2*MAXN][2*MAXN],matriz[MAXN][MAXM];
int processado[2*MAXN];
ll resp;
int R,C,D,ultimox,ultimoy;
inline int calcula(int linha,int cini,int cfim){
	if(cini > cfim) return 0;
	return matriz[linha][cfim] - matriz[linha][cini - 1];
}
void do_Dijkstra(int S){
	memset(processado,0,sizeof(processado));
	priority_queue<ii, vector<ii>, greater<ii> > SSSP;
	SSSP.push(ii(0,S));
	while(!SSSP.empty()){
		int v = SSSP.top().second;
		int dist = SSSP.top().first;
		SSSP.pop();
		if(processado[v]) continue;
		processado[v] = 1;
		tab[S][v] = dist;
		for(int i = 0;i<grafo[v].size();i++){
			int u = grafo[v][i].first, peso = grafo[v][i].second;
			if(!processado[u]) SSSP.push(ii(dist + peso,u));
		}
	}
}
int main(){
	scanf("%d %d",&R,&C);
	for(int i = 1;i<=R;i++){
		for(int j = 1;j<=C;j++){
			scanf("%d",&matriz[i][j]);
			matriz[i][j] += matriz[i][j-1];
		}
	}
	for(int i = 1;i<=R;i++){
		grafo[i].push_back(ii(i + R, calcula(i,2,C) ));
		grafo[i+R].push_back(ii(i,calcula(i,1,C-1)));
	}
	for(int i = 1;i + 1 <= R;i++){
		grafo[i].push_back(ii(i+1,matriz[i+1][1]));
		grafo[i+1].push_back(ii(i,matriz[i][1]));
		grafo[i+R].push_back(ii(i+R+1, calcula(i+1,C,C) ));
		grafo[i+R+1].push_back(ii(i+R,calcula(i,C,C)));
	}
	for(int i = 1;i<=2*R;i++) do_Dijkstra(i);
	scanf("%d",&D);
	ultimox = 1;ultimoy = 1;
	while(D--){
		int x,y;
		scanf("%d %d",&x,&y);
		int best = 1e9;
		if(x == ultimox && y == ultimoy) continue;
		best = min(best, calcula(ultimox,1,ultimoy-1) + tab[ultimox][x] + calcula(x,2,y));
		best = min(best, calcula(ultimox,1,ultimoy-1) + tab[ultimox][x+R] + calcula(x,y,C-1) );
		best = min(best, calcula(ultimox,ultimoy+1,C) + tab[ultimox+R][x] + calcula(x,2,y) );
		best = min(best, calcula(ultimox,ultimoy+1,C) + tab[ultimox+R][x+R] + calcula(x,y,C-1));
		if(ultimox == x){
			if(ultimoy < y) best = min(best, calcula(x,ultimoy+1,y) );
			else best = min(best, calcula(x,y,ultimoy-1) );
		}
		resp += 1LL*best;
		ultimox = x;ultimoy = y;
	}
	resp += 1LL*matriz[1][1];
	printf("%lld\n",resp);
	return 0;
}0;
}