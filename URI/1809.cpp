// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1809
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 101
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<double,ii> dii;
int pai[MAXN],n,m,cenario;
vector<dii> Kruskal;
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x, int y){
	x = find(x);
	y = find(y);
	if(x > y) swap(x,y);
	pai[y] = x;
}
int main(){
	while(scanf("%d %d",&n,&m) && (n||m)){
		if(cenario++) printf("\n");
		Kruskal.clear();
		for(int i=1;i<=n;i++){
			pai[i] = i;
		}
		for(int i=1;i<=m;i++){
			int u,v;
			double peso;
			scanf("%d %d %lf",&u,&v,&peso);
			Kruskal.push_back(MP(1.0 - peso,MP(u,v)));
		}
		sort(Kruskal.begin(),Kruskal.end());
		double prob = 1.0;
		for(int i=m-1;i>=0;i--){
			if(find(Kruskal[i].second.first) != find(Kruskal[i].second.second)){
				join(Kruskal[i].second.first,Kruskal[i].second.second);
				prob *= Kruskal[i].first;
			}
		}
		printf("Cenario %d, probabilidade de interceptacao = %.3lf\n",cenario,1.0 - prob);
	}
	return 0;
}
