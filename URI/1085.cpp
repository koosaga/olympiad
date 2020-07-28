// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1085
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#define MAXN 4001
#define endl '\n'
#define PB push_back
#define MP make_pair
using namespace std;
typedef pair<char,int> i2;
typedef pair<int,i2> i3;
vector<i3> grafo[MAXN];
int processado[200][MAXN],m,n,possivel;
unordered_map<string,int> mapa;
inline void limpa(int x){
	grafo[x].clear();
	for(char caractere = 'a';caractere <= 'z';caractere++){
		processado[caractere][x] = 0;
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(cin >> m && m){
		n = 2;
		possivel = 0;
		string destino,origem;
		cin >> origem >> destino;
		mapa.clear();
		mapa[origem] = 1;
		mapa[destino] = 2;
		limpa(1);
		limpa(2);
		while(m--){
			string s1,s2,s3;
			cin >> s1 >> s2 >> s3;
			if(!mapa.count(s1)){
				mapa[s1] = ++n;
				limpa(n);
			}
			if(!mapa.count(s2)){
				mapa[s2] = ++n;
				limpa(n);
			}
			char inicial = s3[0];
			int tam = s3.size(), u = mapa[s1], v = mapa[s2];
			grafo[u].PB(MP(tam,MP(inicial,v)));
			grafo[v].PB(MP(tam,MP(inicial,u)));
		}
		for(char caractere = 'a';caractere <= 'z';caractere++){
			processado[caractere][1] = 1;
		}
		priority_queue<i3, vector<i3>, greater<i3> > Dijkstra;
		for(int i = 0; i < grafo[1].size();i++){
			Dijkstra.push(grafo[1][i]);
		}
		while(!Dijkstra.empty()){
			i3 davez = Dijkstra.top();
			Dijkstra.pop();
			int percorrido = davez.first, v = davez.second.second;
			char letra = davez.second.first;
			if(v == 2){
				cout << percorrido << endl;
				possivel = 1;
				break;
			}
			if(processado[letra][v]) continue;
			processado[letra][v] = 1;
			for(int i=0;i<grafo[v].size();i++){
				i3 agora = grafo[v][i];
				int u = agora.second.second, peso = agora.first;
				char inicial = agora.second.first;
				if(inicial == letra) continue;
				Dijkstra.push(MP(percorrido + peso,MP(inicial,u)));
			}
		}
		if(possivel == 0) cout << "impossivel" << endl;
	}
	return 0;
}

