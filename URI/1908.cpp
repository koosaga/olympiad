// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1908
#include <cstdio>
#include <queue>
#include <vector>
#define PB push_back
#define MAXN 10100
#define MP make_pair
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
int visitado[MAXN];
vector<int> grafo[MAXN];
int main(){
	int n,m;
	getint(n);
	getint(m);
	while(m--){
		int l;
		getint(l);
		vector<int> vetor;
		for(int i=0;i<l;i++){
			int x;
			getint(x);
			vetor.push_back(x);
		}
		for(int i=0;i<l;i++){
			for(int j=i+1;j<l;j++){
				grafo[vetor[i]].PB(vetor[j]);
				grafo[vetor[j]].PB(vetor[i]);
			}
		}
	}
	queue<ii> bfs;
	bfs.push(MP(1,0));
	while(!bfs.empty()){
		ii davez = bfs.front();
		bfs.pop();
		if (visitado[davez.first]) continue;
		if(davez.first==n){
			printf("%d\n",davez.second);
			return 0;
		}
		visitado[davez.first] = 1;
		for(vector<int>::iterator it = grafo[davez.first].begin();it!=grafo[davez.first].end();it++) bfs.push(MP(*it,davez.second+1));
	}
	return 0;
}

