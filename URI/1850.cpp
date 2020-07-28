// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1850
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN = 1e2 + 1;
const int MAXL = (1 << 8);
int processado[MAXN][MAXN][MAXL];
char mapa[MAXN][MAXN];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int n,m;
struct ponto{
	int d,bit,x,y;
	ponto(int _x,int _y,int _d,int _bit) : x(_x), y(_y), d(_d), bit(_bit) {};
};
inline int valido(ponto o){
	if(o.x < 0) return 0;
	if(o.y < 0) return 0;
	if(o.x >= n) return 0;
	if(o.y >= m) return 0;
	if(mapa[o.x][o.y] == '#') return 0;
	if(processado[o.x][o.y][o.bit]) return 0;
	if(mapa[o.x][o.y] >= 'A' && mapa[o.x][o.y] <= 'G' && !(o.bit & (1 << (mapa[o.x][o.y] - 'A'))) ){
		return 0;
	}
	return 1;
}
int main(){
	while(scanf("%s",mapa[n]) != EOF){
		n++;
	}
	m = strlen(mapa[0]);
	int xaria = -1,yaria = -1;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(mapa[i][j] == '@'){
				xaria = i;
				yaria = j;
				break;
			}
		}
	}
	queue<ponto> bfs;
	ponto ini(xaria,yaria,0,0);
	bfs.push(ini);
	while(!bfs.empty()){
		ponto d = bfs.front();
		bfs.pop();
		if(processado[d.x][d.y][d.bit]) continue;
		processado[d.x][d.y][d.bit] = 1;
		if(mapa[d.x][d.y] == '*'){
			printf("%d\n",d.d);
			return 0;
		}
		int novabit = d.bit;
		if(mapa[d.x][d.y] >= 'a' && mapa[d.x][d.y] <= 'g'){
			novabit |= (1 << (mapa[d.x][d.y] - 'a'));
		}
		for(int i=0;i<4;i++){
			ponto p(d.x + dx[i],d.y + dy[i], d.d + 1, novabit);
			if(valido(p)) bfs.push(p);
		}
	}
	printf("--\n");
	return 0;
}
