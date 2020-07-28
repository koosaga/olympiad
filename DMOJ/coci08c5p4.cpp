// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c5p4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = (1 << 20) + 10;
const int MAXL = 22;

char entrada[MAXL];
int visto[MAXN],mascaras[MAXL],tudo_ligado,H,N;
ll soma_acumulada[MAXN],total_soma;

int main(){

	cin >> N >> H;
	tudo_ligado = (1 << N) - 1;
	for(int i = 0;i<N;i++){
		cin >> entrada;
		for(int j = 0;j<N;j++){
			if(entrada[j] == '1') mascaras[i] |= (1 << j); 
		}
	}

	H--;
	total_soma += __builtin_popcount(mascaras[0]);
	int bitmask_hoje = mascaras[0];
	
	for(int dia = 1;dia<= H;dia++){
		
		if(visto[bitmask_hoje] != 0){
			int comeco = visto[bitmask_hoje];
			int periodo = dia - comeco;
			H = H - dia + 1;
			total_soma += 1LL*(soma_acumulada[dia - 1] - soma_acumulada[comeco - 1])*(H/periodo);
			int resto = H % periodo;
			if(resto != 0) total_soma += soma_acumulada[comeco + resto - 1] - soma_acumulada[comeco - 1];
			break;
		}
		
		int nova_bitmask = 0,somatorio_hoje = 0;
		visto[bitmask_hoje] = dia;
		for(int i = 0;i<N;i++){
			int recebeu = __builtin_popcount(bitmask_hoje & mascaras[i]) + __builtin_popcount((bitmask_hoje ^ tudo_ligado) & mascaras[i])*2;
			somatorio_hoje += recebeu;
			if(recebeu % 2 == 1) nova_bitmask |= (1 << i);
		}
		
		total_soma += somatorio_hoje;
		soma_acumulada[dia] = soma_acumulada[dia - 1] + 1LL*somatorio_hoje;
		bitmask_hoje = nova_bitmask;
	
	}
	
	cout << total_soma << endl;
	
	return 0;
}