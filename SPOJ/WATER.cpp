// Ivan Carvalho
// Solution to https://www.spoj.com/problems/WATER/
#include <bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int> trinca;


const int MAXN = 1e2 + 10;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

int N,M,matriz[MAXN][MAXN],processado[MAXN][MAXN];

inline int valido(int x,int y){
	return min(x,y) >= 1 && x <= N && y <= M;
}

int main(){

	int TC;
	scanf("%d",&TC);

	for(int tc = 1;tc<=TC;tc++){
		
		int ans = 0;
		scanf("%d %d",&N,&M);
		priority_queue<trinca, vector<trinca>, greater<trinca> > pq;
		
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=M;j++){
				scanf("%d",&matriz[i][j]);
				processado[i][j] = 0;
				if(i == 1 || i == N || j == 1 || j == M){
					pq.push(make_tuple(matriz[i][j],i,j));
				}
			}
		}

		while(!pq.empty()){
			trinca davez = pq.top();
			pq.pop();
			int x = get<1>(davez),y = get<2>(davez), h = get<0>(davez);
			if(processado[x][y]) continue;
			processado[x][y] = 1;
			ans += h - matriz[x][y];
			for(int i = 0;i<4;i++){
				int nx = x + dx[i], ny = y + dy[i];
				if(valido(nx,ny) && !processado[nx][ny]) pq.push(make_tuple(max(h,matriz[nx][ny]),nx,ny));
			}
		}

		printf("%d\n",ans);
	}

	return 0;
}
