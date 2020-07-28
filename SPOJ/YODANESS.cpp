// Ivan Carvalho
// Solution to https://www.spoj.com/problems/YODANESS/
#include <iostream>
#include <string>
#include <map>
#define MAXN 30100
#define endl '\n'
using namespace std;
int vetor[MAXN],auxiliar[MAXN],casos;
int merge_sort(int ini, int fim){
	if (ini == fim) return 0;
	int tamanho = 0;
	int meio = (ini + fim)/2;
	int direita = meio + 1;
	int inversoes = merge_sort(ini,meio) + merge_sort(direita,fim);
	for(int esquerda = ini;esquerda <= meio;esquerda++){
		while(direita <= fim && vetor[direita] < vetor[esquerda]){
			auxiliar[tamanho++] = vetor[direita++];
			inversoes += meio - esquerda + 1;
		}
		auxiliar[tamanho++] = vetor[esquerda];
	}
	while(direita<=fim) auxiliar[tamanho++] = vetor[direita++];
	for(int i=ini;i<=fim;i++) vetor[i] = auxiliar[i-ini];
	return inversoes; 
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> casos;
	while(casos--){
		int palavras;
		cin >> palavras;
		for(int i=0;i<=palavras;i++) vetor[i] = auxiliar[i] = 0;
		map<string,int> mapa;
		for(int i=1;i<=palavras;i++){
			string davez;
			cin >> davez;
			mapa[davez] = i;
		}
		for(int i=1;i<=palavras;i++){
			string davez;
			cin >> davez;
			vetor[i] = mapa[davez];
		}
		cout << merge_sort(1,palavras) << endl;
	}
	return 0;
}