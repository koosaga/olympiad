// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1495
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
int main(){
	int n,g;
	while(scanf("%d %d",&n,&g)!=EOF){
		priority_queue<int, vector<int>, greater<int> > gols;
		int empates = 0,vitorias=0;
		while(n--){
			int a,b;
			scanf("%d %d",&a,&b);
			if (a==b) empates++;
			else if (a>b) vitorias++;
			else gols.push(b-a);
		}
		int compra_empates = min(empates,g);
		empates -= compra_empates;
		vitorias += compra_empates;
		g -= compra_empates;
		while(g>0 && !gols.empty()){
			int davez = gols.top();
			gols.pop();
			if (g >= davez + 1){
				g -= davez + 1;
				vitorias++;
			}
			else if (g == davez){
				empates++;
				g -= davez;
			}
		}
		printf("%d\n",empates + (3*vitorias));
	}
	return 0;
}
