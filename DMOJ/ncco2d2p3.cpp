// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ncco2d2p3
#include <bits/stdc++.h>
using namespace std;
typedef pair<short,short> ii;
const int MAXN = 151;
int P,Q,R,N,resp;
short copia[MAXN][MAXN][MAXN],matriz[MAXN][MAXN][MAXN],soma[MAXN][MAXN][MAXN];
int linear[MAXN],antes[MAXN],depois[MAXN];
char entrada[MAXN][MAXN][MAXN];

inline short calcula(int id,int x1,int y1,int x2,int y2){
	return soma[id][x2][y2] - soma[id][x2][y1 - 1] - soma[id][x1-1][y2] + soma[id][x1-1][y1-1];
}

void histograma(){
	stack<ii> pilha;
	pilha.push(ii(-1,0));
	for(int i = 1;i<=N;i++){
		ii davez = ii(linear[i],i);
		while(davez.first < pilha.top().first){
			depois[pilha.top().second] = i;
			pilha.pop();
		}
		if(pilha.top().first == davez.first){
			antes[i] = antes[pilha.top().second];
		}
		else{
			antes[i] = pilha.top().second;
		}
		pilha.push(davez);
	}
	while(!pilha.empty()){
		depois[pilha.top().second] = N+1;
		pilha.pop();
	}
	for(int i = 1;i<=N;i++){
		antes[i]++;
		depois[i]--;
		resp = max(resp, (depois[i] - antes[i] + 1)*linear[i] );
	}
}

inline void solve(){
	for(int x = 1;x<=N;x++){
		for(int y = 1;y<=N;y++){
			if((N - max(x,y) + 1)*N <= resp) break;
			int minimo = resp/N;
			for(int i = 1;i<=N;i++){
				for(int tam = minimo;x + tam - 1 <= N && y + tam - 1 <= N;tam++){
					if(calcula(i,x,y,x + tam - 1,y + tam - 1) == tam*tam){
						linear[i] = tam;
					}
					else break;
				}
			}
			histograma();
		}
	}
}

int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	cin >> Q >> P >> R;
	for(int i = 1;i<=P;i++){
		for(int j = 1;j<=Q;j++){
			cin >> (entrada[i][j] + 1);
		}
	}
	for(int k = 1;k<=P;k++){
		for(int i = 1;i<=Q;i++){
			for(int j = 1;j<=R;j++){
				matriz[k][i][j] = (entrada[k][i][j] == 'N');
			}
		}
	}
	N = max(P,max(Q,R));
	for(int k = 1;k<=N;k++){
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=N;j++){
				soma[k][i][j] = matriz[k][i][j] + soma[k][i][j-1] + soma[k][i-1][j] - soma[k][i-1][j-1];
			}
		}
	}
	solve();
	for(int k = 1;k<=N;k++){
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=N;j++){
				copia[k][i][j] = matriz[k][j][i];
				soma[k][i][j] = copia[k][i][j] + soma[k][i][j-1] + soma[k][i-1][j] - soma[k][i-1][j-1];
			}
		}
	}
	solve();
	for(int k = 1;k<=N;k++){
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=N;j++){
				copia[k][i][j] = matriz[j][k][i];
				soma[k][i][j] = copia[k][i][j] + soma[k][i][j-1] + soma[k][i-1][j] - soma[k][i-1][j-1];
			}
		}
	}
	solve();
	for(int k = 1;k<=N;k++){
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=N;j++){
				copia[k][i][j] = matriz[j][i][k];
				soma[k][i][j] = copia[k][i][j] + soma[k][i][j-1] + soma[k][i-1][j] - soma[k][i-1][j-1];
			}
		}
	}
	solve();
	for(int k = 1;k<=N;k++){
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=N;j++){
				copia[k][i][j] = matriz[i][j][k];
				soma[k][i][j] = copia[k][i][j] + soma[k][i][j-1] + soma[k][i-1][j] - soma[k][i-1][j-1];
			}
		}
	}
	solve();
	for(int k = 1;k<=N;k++){
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=N;j++){
				copia[k][i][j] = matriz[i][k][j];
				soma[k][i][j] = copia[k][i][j] + soma[k][i][j-1] + soma[k][i-1][j] - soma[k][i-1][j-1];
			}
		}
	}
	solve();
	cout << 4 * resp << endl;
	return 0;
}
