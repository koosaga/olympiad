// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1972
#include <cstdio>
#include <queue>
using namespace std;
#define MAXN 510
#define MP make_pair
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
int n,m,herculesx,herculesy,euterpex,euterpey,processado[MAXN][MAXN],matriz[MAXN][MAXN];
inline int valor (char x){
	if (x == '.') return 0;
	if (x == '#') return -1;
	if (x == '1') return 1;
	if (x == '2') return 2;
	if (x == '3') return 3;
	if (x == '4') return 4;
	if (x == '5') return 5;
	if (x == '6') return 6;
	if (x == '7') return 7;
	if (x == '8') return 8;
	if (x == '9') return 9;
	if (x == 'H') return 0;
	if (x == 'E') return 0;
	return -1;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		getchar();
		for(int j=1;j<=m;j++){
			char davez;
			scanf("%c",&davez);
			if (davez == 'H') {
				herculesx = i;
				herculesy = j;
			}
			if (davez == 'E') {
				euterpex = i;
				euterpey = j;
			}
			matriz[i][j] = valor(davez);
		}
	}
	priority_queue<iii, vector<iii> , greater<iii> > dijkstra;
	dijkstra.push(MP(0,MP(herculesx,herculesy)));
	while(!dijkstra.empty()){
		iii davez = dijkstra.top();
		dijkstra.pop();
		int percorrido = davez.first, cord1 = davez.second.first, cord2 = davez.second.second;
		if (cord1 == euterpex && cord2 == euterpey){
			printf("%d\n",percorrido);
			return 0;
		}
		if (processado[cord1][cord2]) continue;
		processado[cord1][cord2] = 1;
		if (cord1 + 1 <= n && matriz[cord1+1][cord2]!=-1) dijkstra.push(MP(percorrido+matriz[cord1+1][cord2],MP(cord1+1,cord2)));
		if (cord1 - 1 > 0 && matriz[cord1-1][cord2]!=-1) dijkstra.push(MP(percorrido+matriz[cord1-1][cord2],MP(cord1-1,cord2)));
		if (cord2 + 1 <= m && matriz[cord1][cord2+1]!=-1) dijkstra.push(MP(percorrido+matriz[cord1][cord2+1],MP(cord1,cord2+1)));
		if (cord2 - 1 > 0 && matriz[cord1][cord2-1]!=-1) dijkstra.push(MP(percorrido+matriz[cord1][cord2-1],MP(cord1,cord2-1))); 
	}
	printf("ARTSKJID\n");
	return 0;
}
