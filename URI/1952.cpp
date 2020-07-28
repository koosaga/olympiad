// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1952
#include <cstdio>
#include <queue>
#define MAXN 101
using namespace std;
int processado[MAXN][MAXN][MAXN],n,m,l,x1,y1,z1,x2,y2,z2;
int dx[30] = {1,-1,1,-1,1,-1,1,-1,2,2,-2,-2,2,2,-2,-2,0,0,0,0,0,0,0,0};
int dy[30] = {2,2,-2,-2,0,0,0,0,1,-1,1,-1,0,0,0,0,1,-1,1,-1,2,2,-2,-2};
int dz[30] = {0,0,0,0,2,2,-2,-2,0,0,0,0,1,-1,1,-1,2,2,-2,-2,1,-1,1,-1};
struct ponto{
	int x,y,z,percorrido;
	ponto(int p,int q,int r,int novopercorrido) : x(p), y(q), z(r), percorrido(novopercorrido) {} ;
};
inline int valido(ponto d){
	if(d.x <= 0) return 0;
	if(d.x > n) return 0;
	if(d.y <= 0) return 0;
	if(d.y > m) return 0;
	if(d.z <= 0) return 0;
	if(d.z > l) return 0;
	if(processado[d.x][d.y][d.z]) return 0;
	return 1;
}
int main(){
	scanf("%d %d %d",&n,&m,&l);
	scanf("%d %d %d",&x1,&y1,&z1);
	scanf("%d %d %d",&x2,&y2,&z2);
	queue<ponto> bfs;
	ponto ini(x1,y1,z1,0);
	bfs.push(ini);
	while(!bfs.empty()){
		ponto d = bfs.front();
		bfs.pop();
		if(processado[d.x][d.y][d.z]) continue;
		if(d.x == x2 && d.y == y2 && d.z == z2){
			printf("%d\n",d.percorrido);
			return 0;
		}
		processado[d.x][d.y][d.z] = 1;
		for(int i=0;i<24;i++){
			ponto davez(d.x + dx[i],d.y + dy[i],d.z + dz[i],d.percorrido+1);
			if(valido(davez)) bfs.push(davez);
		}
	}
	return 0;
}
