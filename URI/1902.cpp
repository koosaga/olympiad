// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1902
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;
typedef vector<int> vi;
#define MAXN 100100
#define endl '\n'
#define PB push_back
vi grafo[MAXN],transposto[MAXN];
int visitado[MAXN],contador,resposta;
stack<int> pilha;
unordered_map<string, int> mapa;
void dfs1(int u){
	visitado[u]=1;
	for(vi::iterator it=grafo[u].begin();it!=grafo[u].end();it++){
		int v = *it;
		if (!visitado[v]){
			dfs1(v);
		}
	}
	pilha.push(u);
}
int dfs2(int u){
	int retornar = 1;
	visitado[u]=0;
	for(vi::iterator it=transposto[u].begin();it!=transposto[u].end();it++){
		int v = *it;
		if (visitado[v]){
			retornar += dfs2(v);
		}
	}
	return retornar;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string nome1,nome2;
	while (cin >> nome1 >> nome2){
		if (!mapa.count(nome1)) mapa[nome1]=contador++;
		if (!mapa.count(nome2)) mapa[nome2]=contador++;
		int codigo1 = mapa[nome1];
		int codigo2 = mapa[nome2];
		grafo[codigo1].PB(codigo2);
		transposto[codigo2].PB(codigo1);
	}
	for(int i=0;i<contador;i++) if (!visitado[i]) dfs1(i);
	while(!pilha.empty()){
		int vertice = pilha.top();
		pilha.pop();
		if (visitado[vertice]){
			int numero = dfs2(vertice);
			numero--;
			if (numero) resposta++;
		}
	}
	cout << resposta << endl;
	return 0;
}
