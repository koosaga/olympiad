// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1955
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#define MAXN 1001
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
vector<int> grafo[MAXN];
int cor[MAXN],visitado[MAXN],n;
int main(){
	memset(cor,-1,sizeof(cor));
	getint(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int davez;
			getint(davez);
			if (!davez){
				grafo[i].push_back(j);
			}
		}
	}
	cor[1] = 1;
	queue<int> bfs;
	bfs.push(1);
	while(!bfs.empty()){
		int v = bfs.front();
		bfs.pop();
		if (visitado[v]) continue;
		visitado[v] = 1;
		for(int i=0;i<grafo[v].size();i++){
			int u = grafo[v][i];
			if (cor[u] == cor[v]){
				printf("Fail!\n");
				return 0;
			}
			cor[u] = !cor[v];
			bfs.push(u);
		}
	}
	printf("Bazinga!\n");
	return 0;
}
