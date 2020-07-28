// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1057
#include <cstdio>
#include <queue>
#define MAXN 9
using namespace std;
int dx[5] = {1,-1,0,0};
int dy[5] = {0,0,-1,1}; 
struct ponto{
	int x1,y1,x2,y2,x3,y3,percorrido;
	ponto(int _x1,int _y1,int _x2,int _y2,int _x3,int _y3,int _percorrido) : x1(_x1),y1(_y1),x2(_x2),y2(_y2),x3(_x3),y3(_y3),percorrido(_percorrido) {};
};
int matriz[MAXN][MAXN][MAXN][MAXN][MAXN][MAXN],n;
char mapa[MAXN][MAXN];
inline int cord(int x, int y){
	if(x >= n) return 0;
	if(y >= n) return 0;
	if(x < 0) return 0;
	if(y < 0) return 0;
	return 1;
}
inline int valido(ponto d){
	if(d.x1 == d.x2 && d.y1 == d.y2) return 0;
	if(d.x1 == d.x3 && d.y1 == d.y3) return 0;
	if(d.x2 == d.x3 && d.y2 == d.y3) return 0;
	return 1;
}
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc = 1;tc<=TC;tc++){
		scanf("%d",&n);
		int possivel = 0;
		for(int i1=0;i1<n;i1++){
			for(int i2=0;i2<n;i2++){
				for(int i3=0;i3<n;i3++){
					for(int i4=0;i4<n;i4++){
						for(int i5=0;i5<n;i5++){
							for(int i6=0;i6<n;i6++){
								matriz[i1][i2][i3][i4][i5][i6] = 0;
							}
						}
					}
				}
			}
		}
		int x1,y1,x2,y2,x3,y3;
		for(int i=0;i<n;i++){
			scanf("%s",mapa[i]);
			for(int j=0;j<n;j++){
				if(mapa[i][j] == 'A'){
					x1 = i;
					y1 = j;
				}
				if(mapa[i][j] == 'B'){
					x2 = i;
					y2 = j;
				}
				if(mapa[i][j] == 'C'){
					x3 = i;
					y3 = j;
				}
			}
		}
		ponto ini(x1,y1,x2,y2,x3,y3,0);
		queue<ponto> bfs;
		bfs.push(ini);
		while(!bfs.empty()){
			ponto d = bfs.front();
			bfs.pop();
			//printf("%d %d %d %d %d %d\n",d.x1,d.y1,d.x2,d.y2,d.x3,d.y3);
			if(mapa[d.x1][d.y1] == 'X' && mapa[d.x2][d.y2] == 'X' && mapa[d.x3][d.y3] == 'X'){
				possivel = 1;
				printf("Case %d: %d\n",tc,d.percorrido);
				break;
			}
			if(matriz[d.x1][d.y1][d.x2][d.y2][d.x3][d.y3]) continue;
			matriz[d.x1][d.y1][d.x2][d.y2][d.x3][d.y3] = 1;
			for(int i=0;i<4;i++){
				ponto agora(d.x1 + (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1+dx[i]][d.y1] != '#' ? dx[i] : 0),d.y1 + (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1][d.y1+dy[i]] != '#' ? dy[i] : 0),d.x2 + (cord(d.x2 + dx[i], d.y2 + dy[i]) && mapa[d.x2+dx[i]][d.y2] != '#' ? dx[i] : 0),d.y2 + (cord(d.x2 + dx[i], d.y2 + dy[i]) && mapa[d.x2][d.y2+dy[i]] != '#' ? dy[i] : 0),d.x3 + (cord(d.x3 + dx[i],d.y3 + dy[i]) && mapa[d.x3+dx[i]][d.y3] != '#' ? dx[i] : 0), d.y3 + (cord(d.x3 + dx[i],d.y3 + dy[i]) && mapa[d.x3][d.y3+dy[i]] != '#' ? dy[i] : 0), d.percorrido+1);
				if(valido(agora)) bfs.push(agora);
				else{
					if(agora.x1 == agora.x2 && agora.y1 == agora.y2){
						agora.x1 -= (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1+dx[i]][d.y1] != '#' ? dx[i] : 0);
						agora.y1 -= (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1][d.y1+dy[i]] != '#' ? dy[i] : 0);
						if(valido(agora)) bfs.push(agora);
						agora.x1 += (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1+dx[i]][d.y1] != '#' ? dx[i] : 0);
						agora.y1 += (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1][d.y1+dy[i]] != '#' ? dy[i] : 0);
						agora.x2 -= (cord(d.x2 + dx[i],d.y2 + dy[i]) && mapa[d.x2+dx[i]][d.y2] != '#' ? dx[i] : 0);
						agora.y2 -= (cord(d.x2 + dx[i],d.y2 + dy[i]) && mapa[d.x2][d.y2+dy[i]] != '#' ? dy[i] : 0);
						if(valido(agora)) bfs.push(agora);
					}
					else if(agora.x1 == agora.x3 && agora.y1 == agora.y3){
						agora.x1 -= (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1+dx[i]][d.y1] != '#' ? dx[i] : 0);
						agora.y1 -= (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1][d.y1+dy[i]] != '#' ? dy[i] : 0);
						if(valido(agora)) bfs.push(agora);
						agora.x1 += (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1+dx[i]][d.y1] != '#' ? dx[i] : 0);
						agora.y1 += (cord(d.x1 + dx[i],d.y1 + dy[i]) && mapa[d.x1][d.y1+dy[i]] != '#' ? dy[i] : 0);
						agora.x3 -= (cord(d.x3 + dx[i],d.y3 + dy[i]) && mapa[d.x3+dx[i]][d.y3] != '#' ? dx[i] : 0);
						agora.y3 -= (cord(d.x3 + dx[i],d.y3 + dy[i]) && mapa[d.x3][d.y3+dy[i]] != '#' ? dy[i] : 0);
						if(valido(agora)) bfs.push(agora);
					}
					else if(agora.x2 == agora.x3 && agora.y2 == agora.y3){
						agora.x3 -= (cord(d.x3 + dx[i],d.y3 + dy[i]) && mapa[d.x3+dx[i]][d.y3] != '#' ? dx[i] : 0);
						agora.y3 -= (cord(d.x3 + dx[i],d.y3 + dy[i]) && mapa[d.x3][d.y3+dy[i]] != '#' ? dy[i] : 0);
						if(valido(agora)) bfs.push(agora);
						agora.x3 += (cord(d.x3 + dx[i],d.y3 + dy[i]) && mapa[d.x3+dx[i]][d.y3] != '#' ? dx[i] : 0);
						agora.y3 += (cord(d.x3 + dx[i],d.y3 + dy[i]) && mapa[d.x3][d.y3+dy[i]] != '#' ? dy[i] : 0);
						agora.x2 -= (cord(d.x2 + dx[i],d.y2 + dy[i]) && mapa[d.x2+dx[i]][d.y2] != '#' ? dx[i] : 0);
						agora.y2 -= (cord(d.x2 + dx[i],d.y2 + dy[i]) && mapa[d.x2][d.y2+dy[i]] != '#' ? dy[i] : 0);
						if(valido(agora)) bfs.push(agora);
					}
				}
			}
		}
		if(!possivel)printf("Case %d: trapped\n",tc);
	}
	return 0;
}
