// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2047
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#define MAXN 511
#define endl '\n'
using namespace std;
vector<int> grafo[MAXN];
int cap[MAXN][MAXN],processado[MAXN],anterior[MAXN],alvo,n,instancia;
int augmenting_path(){
	for(int i=1;i<=n;i++){
		processado[i] = 0;
		anterior[i] = -1;
	}
	anterior[1] = 1;
	queue<int> bfs;
	bfs.push(1);
	while(!bfs.empty()){
		int v = bfs.front();
		bfs.pop();
		if(processado[v]) continue;
		processado[v] = 1;
		if(v == alvo) break;
		for(int u : grafo[v]){
			if(anterior[u] == -1 && cap[v][u] > 0){
				bfs.push(u);
				anterior[u] = v;
			}
		}
	}
	if(!processado[alvo]) return 0;
	vector<int> caminho;
	caminho.push_back(alvo);
	int atual = alvo;
	while(atual != 1){
		caminho.push_back(anterior[atual]);
		atual = anterior[atual];
	}
	reverse(caminho.begin(),caminho.end());
	int temp = 201;
	for(int i=0;i + 1 < caminho.size();i++ ){
		temp = min(temp, cap[caminho[i]][caminho[i+1]] );
	}
	for(int i=0;i + 1 < caminho.size();i++ ){
		cap[caminho[i]][caminho[i+1]] -= temp;
		cap[caminho[i+1]][caminho[i]] += temp;
	}
	return 1;
}
int Edmond(){
	while(true){
		if(!augmenting_path()) break;
	}
	for(int i : grafo[1]){
		if(cap[1][i]) return 0;
	}
	return 1;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int iniciais;
	while(cin >> iniciais && iniciais){
		unordered_map<string,int> conversao;
		for(int i=0;i<MAXN;i++){
			grafo[i].clear();
		}
		memset(cap,0,sizeof(cap));
		n = 1;
		while(iniciais--){
			string s;
			int aguenta;
			cin >> s >> aguenta;
			conversao[s] = ++n;
			cap[1][n] = cap[n][1] = aguenta;
			grafo[1].push_back(n);
			grafo[n].push_back(1);
		}
		int arestas;
		string destino;
		cin >> arestas >> destino;
		conversao[destino] = ++n;
		alvo = n;
		while(arestas--){
			string a,b;
			int aguenta;
			cin >> a >> b >> aguenta;
			if(!conversao.count(a)) conversao[a] = ++n;
			if(!conversao.count(b)) conversao[b] = ++n;
			int u = conversao[a];
			int v = conversao[b];
			grafo[u].push_back(v);
			grafo[v].push_back(u);
			cap[u][v] = cap[v][u] = aguenta;
		}
		cout << "Instancia " << ++instancia << endl;
		if(Edmond()) cout << "viavel" << endl << endl;
		else cout << "inviavel" << endl << endl;
	}
	return 0;
}
