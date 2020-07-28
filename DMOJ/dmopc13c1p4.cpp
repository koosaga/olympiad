// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc13c1p4
#include <bits/stdc++.h>
#define MAXN 60
using namespace std;
typedef tuple<int,int,int,int> quadra;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
char entrada[MAXN][MAXN];
int processado[MAXN][MAXN];
int inix,iniy,fimx,alvox,alvoy,n,m;
inline int H(int x,int y){
	return abs(x - alvox) + abs(y - alvoy);
}
inline int valido(int x,int y){
	return x >= 0 && y >= 0 && x < n && y < m && entrada[x][y] != 'X'  && !processado[x][y];
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int TC;
	cin >> TC;
	while(TC--){
		cin >> m >> n;
		for(int i=0;i<n;i++){
			cin >> entrada[i];
			for(int j=0;j<m;j++){
				processado[i][j] = 0;
				if(entrada[i][j] == 'C'){
					inix = i;
					iniy = j;
				}
				if(entrada[i][j] == 'W'){
					alvox = i;
					alvoy = j;
				}
			}
		}
		int possivel = 0;
		priority_queue< quadra, vector<quadra>, greater<quadra> > Astar;
		Astar.push(make_tuple(H(inix,iniy),0,inix,iniy));
		while(!Astar.empty()){
			quadra davez = Astar.top();
			Astar.pop();
			int heuristica = get<0>(davez),dist = get<1>(davez),x = get<2>(davez),y = get<3>(davez);
			if(x == alvox && y == alvoy){
				cout << dist << '\n';
				possivel = 1;
				break;
			}
			if(processado[x][y]){
				continue;
			}
			processado[x][y] = 1;
			if(dist == 59){
				continue;
			}
			for(int i=0;i<4;i++){
				int nx = x + dx[i], ny = y + dy[i];
				if(valido(nx,ny)) Astar.push(make_tuple(H(nx,ny) + dist + 1,dist + 1,nx,ny));
			}
		}
		if(!possivel) cout << "#notworth\n";
	}
	return 0;
}