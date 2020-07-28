// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bfs17p3
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 3010;
int n,m,X1[MAXN],Y1[MAXN],R1[MAXN],X2[MAXN],Y2[MAXN],R2[MAXN],ini1,ini2,max1,max2,obj1,obj2,min1,min2;
int processado1[MAXN],processado2[MAXN];
int sq(int x){return x*x;}
int euclid(int x,int y){return sq(x) + sq(y);}
int main(){
	scanf("%d %d",&n,&m);
	min1 = 2*MAXN;
	min2 = 2*MAXN;
	for(int i = 1;i<=n;i++){
		scanf("%d %d %d",&X1[i],&Y1[i],&R1[i]);
		if(Y1[i] > max1){
			max1 = Y1[i];
			ini1=  i;
		}
		if(R1[i] == 9001){
			obj1 = i;
		}
	}
	for(int i = 1;i<=m;i++){
		scanf("%d %d %d",&X2[i],&Y2[i],&R2[i]);
		if(Y2[i] > max2){
			max2 = Y2[i];
			ini2=  i;
		}
		if(R2[i] == 9001){
			obj2 = i;
		}
	}
	queue<ii> bfs1;
	bfs1.push(ii(0,ini1));
	while(!bfs1.empty()){
		int v = bfs1.front().second;
		int perc = bfs1.front().first;
		bfs1.pop();
		if(processado1[v] == 1) continue;
		processado1[v] = 1;
		if(v == obj1){
			min1 = perc;
			break;
		}
		for(int u = 1;u<=n;u++){
			if(processado1[u] != 0) continue;
			int vaivai = euclid(X1[v] - X1[u],Y1[v] - Y1[u]);
			if(vaivai <= R1[v]*R1[v]){
				processado1[u] = 2;
				bfs1.push(ii(perc+1,u));
			}
		}
	}
	queue<ii> bfs2;
	bfs2.push(ii(0,ini2));
	while(!bfs2.empty()){
		int v = bfs2.front().second;
		int perc = bfs2.front().first;
		bfs2.pop();
		if(processado2[v] == 1) continue;
		processado2[v] = 1;
		if(v == obj2){
			min2 = perc;
			break;
		}
		for(int u = 1;u<=m;u++){
			if(processado2[u] != 0) continue;
			int vaivai = euclid(X2[v] - X2[u],Y2[v] - Y2[u]);
			if(vaivai <= R2[v]*R2[v]){
				processado2[u] = 2;
				bfs2.push(ii(perc+1,u));
			}
		}
	}
	if(min1 < min2){
		printf("We are the champions!\n");
	}
	else if(min1 == min2){
		printf("SUDDEN DEATH\n");
	}
	else{
		printf(":'(\n");
	}
	return 0;
};
	}
	return 0;
}