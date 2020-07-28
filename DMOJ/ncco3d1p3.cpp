// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ncco3d1p3
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef long long ll;

const int MAXN = 32;
const int INF = 1e9;
int dx[8] = {1,1,-1,-1,2,2,-2,-2};
int dy[8] = {2,-2,2,-2,1,-1,1,-1};

int N,M,matriz[MAXN][MAXN],x_i,y_i,x_f,y_f,jafoi[MAXN][MAXN],processado[MAXN][MAXN],iteracao,distancia[MAXN][MAXN];
ll dp[MAXN][MAXN];
vector<ii> pilha;

inline int valido(int a,int b){
	return min(a,b) >= 1 && a <= N && b <= M && (matriz[a][b] != 2);
}

void dfs(int x,int y){
	
	processado[x][y] = iteracao;
	
	for(int i = 0;i<8;i++){
		int nx = x + dx[i],ny = y + dy[i];
		
		if(!valido(nx,ny)) continue;
		
		if(matriz[nx][ny] == 0){
			if(processado[nx][ny] == iteracao) continue;
			processado[nx][ny] = iteracao;
			pilha.push_back(ii(nx,ny));
		}
		else{
			if(processado[nx][ny] == iteracao) continue;
			dfs(nx,ny);
		}
		
	}

}

int main(){
	
	scanf("%d %d",&N,&M);

	for(int i = 1;i<=N;i++){
		for(int j = 1;j<=M;j++){

			distancia[i][j] = INF;
			scanf("%d",&matriz[i][j]);
			
			if(matriz[i][j] == 3){
				x_i = i,y_i = j;
				matriz[i][j] = 0;
			}
			else if(matriz[i][j] == 4){
				x_f = i,y_f = j;
				matriz[i][j] = 0;
			
			}
		}
	}

	queue<ii> bfs;
	distancia[x_i][y_i] = 0;
	dp[x_i][y_i] = 1;
	bfs.push(ii(x_i,y_i));

	while(!bfs.empty()){
		
		int x = bfs.front().first, y = bfs.front().second;
		bfs.pop();
		
		if(jafoi[x][y]) continue;
		jafoi[x][y] = 1;

		iteracao++;
		dfs(x,y);
		//printf("X %d Y %d D %d P %d\n",x,y,distancia[x][y],(int)pilha.size());
		for(ii novo : pilha){
			
			int nx = novo.first, ny = novo.second;
			//printf("NX %d NY %d D %d\n",nx,ny,distancia[nx][ny]);
			if(distancia[x][y] + 1 > distancia[nx][ny]){
				continue;
				//printf("Caso 1\n");
			}
			else if(distancia[x][y] + 1 < distancia[nx][ny]){
				//printf("Caso 2\n");
				distancia[nx][ny] = distancia[x][y] + 1;
				dp[nx][ny] = dp[x][y];
				bfs.push(novo);
			}
			else{
				//printf("Caso 3\n");
				dp[nx][ny] += dp[x][y];
			}

		}
		pilha.clear();

	}

	if(jafoi[x_f][y_f]){
		printf("%d\n",distancia[x_f][y_f] - 1);
		printf("%lld\n",dp[x_f][y_f]);
	}
	else{
		printf("-1\n");
	}

	return 0;
}