// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c4p2
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int ALPHABET_SIZE = 26;

vector<int> frequencia;
int atual,delta,last,antigoatual;

int mod_sum(int x,int a){
	return (((x + a) % ALPHABET_SIZE) + ALPHABET_SIZE) % ALPHABET_SIZE;
}

int main(){
	frequencia.assign(ALPHABET_SIZE,0);
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	int Q;
	cin >> Q;
	delta = 1;
	while(Q--){
		string s;
		cin >> s;
		if(s[0] == 'U'){
			antigoatual = atual;
			int n;
			char c;
			cin >> n >> c;
			int qtd = n - last;
			int letra = c - 'a';
			vector<int> copia = frequencia;
			for(int i = 0;i<ALPHABET_SIZE;i++) copia[i] += qtd/ALPHABET_SIZE;
			qtd %= ALPHABET_SIZE;
			while(qtd > 0){
				copia[atual]++;
				atual = mod_sum(atual,delta);
				qtd--;
			}
			cout << copia[letra] << endl;
			atual = antigoatual;
		}
		else{
			int n;
			cin >> n;
			int qtd = n - last;
			for(int i = 0;i<ALPHABET_SIZE;i++) frequencia[i] += qtd/ALPHABET_SIZE;
			qtd %= ALPHABET_SIZE;
			while(qtd > 0){
				frequencia[atual]++;
				atual = mod_sum(atual,delta);
				qtd--;
			}
			delta *= -1;
			atual = mod_sum(atual,2*delta);
			last = n;
		}
	}
	return 0;
}