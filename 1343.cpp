// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1343
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#define MAXN 65
#define MAXL 9
#define MP make_pair
#define PB push_back
using namespace std;
typedef vector<int> vi;
typedef pair<int,vi> ivi;
int dx[8] = {1,1,-1,-1,2,2,-2,-2};
int dy[8] = {2,-2,2,-2,1,-1,1,-1};
vi grafo[MAXN];
int matriz[MAXL][MAXL],contador,n;
set<vi> conjunto;
inline int perdedor(vi pecas){
	for(int i=0;i<pecas.size() - 1;i++){
		if(pecas[i] >= MAXN) return 1;
	}
	return 0;
}
inline int vencedor(vi pecas){
	return pecas.size() == 1;
}
inline int valido(int x,int y){
	return x >= 1 && y >= 1 && x < MAXL && y < MAXL;
}
int main(){
	for(int i=1;i<MAXL;i++){
		for(int j=1;j<MAXL;j++){
			matriz[i][j] = ++contador;
		}
	}
	for(int i=1;i< MAXL;i++){
		for(int j=1;j<MAXL;j++){
			int id = matriz[i][j];
			for(int k=0;k<8;k++){
				if(valido(i + dx[k],j + dy[k])) grafo[id].PB(matriz[i + dx[k]][j + dy[k]]);
			}
		}
	}
	//for(int i=1;i<MAXN;i++){
	//	printf("%d :",i);
	//	for(int j=0;j<grafo[i].size();j++){
	//		printf(" %d",grafo[i][j]);
	//	}
	//	printf("\n");
	//}
	while(scanf("%d",&n) && n){
		vi inicial;
		conjunto.clear();
		for(int i=0;i<=n;i++){
			int peca;
			scanf("%d",&peca);
			inicial.PB(peca);
		}
		int possivel = 0;
		queue<ivi> fila;
		fila.push(MP(0,inicial));
		while(!fila.empty()){
			ivi davez = fila.front();
			fila.pop();
			int movimentos = davez.first;
			vi pecas = davez.second;
			if(conjunto.count(pecas)) continue;
			conjunto.insert(pecas);
			//printf("%d movimentos :",movimentos);
			//for(int i=0;i<pecas.size();i++){
			//	printf(" %d",pecas[i]);
			//}
			//printf("\n");
			if(perdedor(pecas)){
				//printf("Perdedor\n");
				continue;
			}
			if(vencedor(pecas)){
				possivel = 1;
				printf("%d\n",movimentos);
				break;
			}
			int cavalo = pecas[pecas.size()-1];
			for(int i=0;i<grafo[cavalo].size();i++){
				int proximo = grafo[cavalo][i];
				vi novo;
				for(int j=0;j<pecas.size() - 1;j++){
					int peao = pecas[j];
					if(peao == proximo) continue;
					novo.PB(peao+8);
				}
				novo.PB(proximo);
				fila.push(MP(movimentos+1,novo));
			}
		}
		if(!possivel) printf("impossible\n");
	}
	return 0;
}
