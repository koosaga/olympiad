// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1897
#include <cstdio>
#include <queue>
#include <set>
using namespace std;
int main(){
	queue< pair<int,int> > fila;
	set<int> jafoi;
	int n,m;
	scanf("%d %d",&n,&m);
	fila.push(make_pair(n,0));
	while(true){
		pair<int,int> davez = fila.front();
		int valor = davez.first,operacoes=davez.second;
		fila.pop();
		if (valor==m){
			printf("%d\n",operacoes);
			break;
		}
		if (!jafoi.count(valor)){
			jafoi.insert(valor);
			fila.push(make_pair(valor*2,operacoes+1));
			fila.push(make_pair(valor*3,operacoes+1));
			fila.push(make_pair(valor/2,operacoes+1));
			fila.push(make_pair(valor/3,operacoes+1));
			fila.push(make_pair(valor+7,operacoes+1));
			fila.push(make_pair(valor-7,operacoes+1));
		}
	}
	return 0;
}
