// Ivan Carvalho
// Solution to https://www.spoj.com/problems/HIKE/
#include <cstdio>
#include <queue>
#define MAXN 51
using namespace std;
struct position{
	int p1,p2,p3;
	int distance;
};
char matrix[MAXN][MAXN];
int processado[MAXN][MAXN][MAXN],n,s1,s2,s3,possivel;
int main(){
	while(scanf("%d",&n) && n){
		possivel = 0;
		scanf("%d %d %d",&s1,&s2,&s3);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf(" %c",&matrix[i][j]);
				for(int k=1;k<=n;k++){
					processado[i][j][k] = 0;
				}
			}
		}
		position start;
		start.p1 = s1;
		start.p2 = s2;
		start.p3 = s3;
		start.distance = 0;
		queue<position> bfs;
		bfs.push(start);
		while(!bfs.empty()){
			position d = bfs.front();
			bfs.pop();
			if(d.p1 == d.p2 && d.p2 == d.p3){
				printf("%d\n",d.distance);
				possivel = 1;
				break;
			}
			if(processado[d.p1][d.p2][d.p3]) continue;
			processado[d.p1][d.p2][d.p3] = 1;
			for(int i=1;i<=n;i++){
				if(matrix[i][d.p1] == matrix[d.p2][d.p3]){
					position temp;
					temp.p1 = i;
					temp.p2 = d.p2;
					temp.p3 = d.p3;
					temp.distance = d.distance + 1;
					bfs.push(temp);
				}
				if(matrix[i][d.p2] == matrix[d.p1][d.p3]){
					position temp;
					temp.p1 = d.p1;
					temp.p2 = i;
					temp.p3 = d.p3;
					temp.distance = d.distance + 1;
					bfs.push(temp);
				}
				if(matrix[i][d.p3] == matrix[d.p2][d.p1]){
					position temp;
					temp.p1 = d.p1;
					temp.p2 = d.p2;
					temp.p3 = i;
					temp.distance = d.distance + 1;
					bfs.push(temp);
				}
			}
		}
		if(!possivel) printf("impossible\n");
	}
	return 0;
}