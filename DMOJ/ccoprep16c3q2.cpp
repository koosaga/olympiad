// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoprep16c3q2
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 2*1e2 + 10;
int N,M;
double gauss[MAXN][MAXN];
vector<ii> grafo[MAXN];
void exibe(){
	for(int i = 1;i<=2*N;i++){
		for(int j = 1;j<=2*N+1;j++){
			printf("%.3lf ",gauss[i][j]);
		}
		printf("\n");
	}
	for(int i = 0;i<20;i++) printf("#");
	printf("\n");
}
double processa(int pot){
	memset(gauss,0,sizeof(gauss));
	for(int v =  1;v<=N;v++){
		int tam = grafo[v].size();
		double inverso = 1.0/double(max(tam,1));
		gauss[v][v] += 1.0;
		gauss[v+N][v+N] += 1.0;
		if(v == N) continue;
		for(int i = 0;i<grafo[v].size();i++){
			int u = grafo[v][i].first;
			int peso = (grafo[v][i].second & ( 1 << pot)) ? (1) : (0);
			if(peso == 0){
				gauss[v][u] += -inverso;
				gauss[v+N][u+N] += -inverso;  
			}
			else{
				gauss[v][u+N] += -inverso;
				gauss[v+N][u] += -inverso;
			}
		}
	}
	//exibe();
	gauss[2*N][2*N+1] += 1.0;
	for(int linha = 2*N;linha>=1;linha--){
		for(int nxtlinha = 1;nxtlinha<linha;nxtlinha++){
			double razao = gauss[nxtlinha][linha]/gauss[linha][linha];
			for(int coluna = 1;coluna<=2*N+1;coluna++){
				gauss[nxtlinha][coluna] -= razao*gauss[linha][coluna];
			}
		}
		//exibe();
	} 
	return gauss[1][2*N+1]/gauss[1][1];
}
int main(){
	double expected = 0;
	cin >> N >> M;
	for(int i = 1;i<=M;i++){
		int u,v,w;
		cin >> u >> v >> w;
		grafo[u].push_back(ii(v,w));
		if(u != v) grafo[v].push_back(ii(u,w));
	}
	for(int pot = 0;pot<=30;pot++){
		expected += processa(pot)*((1 << pot));
	}
	printf("%.3lf\n",expected);
	return 0;
}
