// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1317
#include <iostream>
#include <vector>
#define MAXN 21
#define endl '\n'
using namespace std;
vector<int> grafo[MAXN];
int processado[MAXN];
vector<string> atributos[MAXN];
int t1,t2,n;
string a1,a2,a3;
void dfs(int x){
	processado[x] = 1;
	atributos[x].pop_back();
	if(grafo[x].size() < t1) atributos[x].push_back(a1);
	else if(grafo[x].size() < t2) atributos[x].push_back(a2);
	else atributos[x].push_back(a3);
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(!processado[v]) dfs(v);
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(cin >> n && n){
		for(int i=1;i<=n;i++){
			atributos[i].clear();
			grafo[i].clear();
		}
		for(int i=1;i<=n;i++){
			int j;
			while(cin >> j && j){
				grafo[i].push_back(j);
			}
		}
		int ini;
		while(cin >> ini && ini){
			cin >> t1 >> t2 >> a1 >> a2 >> a3;
			for(int i=1;i<=n;i++){
				processado[i] = 0;
				atributos[i].push_back(a1);
			}
			dfs(ini);
		}
		for(int i=1;i<=n;i++){
			string nome;
			cin >> nome;
			cout << nome << ": ";
			for(int j=0;j<atributos[i].size();j++){
				cout << atributos[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}
