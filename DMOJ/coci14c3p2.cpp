// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c3p2
#include <cstdio>
const int MAXN = 1e5 + 10;
int fav[MAXN],hate[MAXN],whochanges[MAXN],visited[MAXN],N,M,P,resp;
int main(){
	scanf("%d %d %d",&N,&M,&P);
	for(int i=1;i<=N;i++){
		scanf("%d %d",&fav[i],&hate[i]);
	}
	for(int i = N;i >= 1;i--){
		whochanges[hate[i]] = i;
	}
	for(int vez = 1;vez<=2*M;vez++){
		if(visited[P]){
			printf("-1\n");
			return 0;
		}
		visited[P] = 1;
		if(whochanges[P] == 0){
			printf("%d\n",resp);
			return 0;
		}
		P = fav[whochanges[P]];
		resp++;
	}
	return 0;
}