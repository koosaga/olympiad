// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c5p5
#include <cstdio>
#include <set>
#include <queue>
#include <algorithm>
#define MAXN 501
#define INF 511100
using namespace std;
set<int> matriz[MAXN];
int R,S;
inline int sq(int x){
	return x*x;
}
inline int sumsq(int x,int y){
	return sq(x) + sq(y);
}
int main(){
	scanf("%d %d",&R,&S);
	for(int i=1;i<=R;i++){
		for(int j=1;j<=S;j++){
			char c;
			scanf(" %c",&c);
			if(c == 'x') matriz[i].insert(j);
		}
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int x,y,dist = INF;
		scanf("%d %d",&x,&y);
		queue<int> bfs;
		bfs.push(x);
		if(x -1 >= 1) bfs.push(x-1);
		if(x + 1 <= R) bfs.push(x + 1);
		while(!bfs.empty()){
			int v = bfs.front();
			bfs.pop();
			if(sq(x - v) >= dist) break;
			set<int>::iterator it = matriz[v].lower_bound(y);
			if(it != matriz[v].end()){
				dist = min(dist, sumsq(v - x, *it - y) );
			}
			if(it != matriz[v].begin()){
				dist = min(dist, sumsq(v - x, *prev(it) - y) );
			}
			if(v < x && v -1 >= 1) bfs.push(v-1);
			if(v > x && v + 1 <= R) bfs.push(v+1);
		}
		matriz[x].insert(y);
		printf("%d\n",dist);
	}
	return 0;
}