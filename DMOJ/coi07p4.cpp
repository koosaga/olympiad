// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coi07p4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5200;
const int MAXL = 20;
const int MAXD = 10;
const int lista_primos[4] = {2,3,5,7};

map<int,int> conversao;
vector<int> digitos;
int visitado[MAXL][MAXN][2],iteracao,tamanho;
ll dp[MAXL][MAXN][2],A,B;
int numero[MAXN],vaipara[MAXN][MAXD],raizB;

void brute(int atual){
	if(conversao.count(atual)) return;
	int novo = conversao.size() + 1;
	conversao[atual] = novo;
	numero[novo] = atual;
	for(int i = 0;i<4;i++){
		ll proximo = 1LL*atual*lista_primos[i];
		if(proximo > raizB) continue;
		brute(proximo);
	}
}

ll solve(int posicao,int idx,int flag){
	if(posicao == tamanho) return (numero[idx] == 1);
	if(visitado[posicao][idx][flag] == iteracao) return dp[posicao][idx][flag];
	visitado[posicao][idx][flag] = iteracao;
	ll ans = 0;
	int limite = 9;
	if(flag) limite = digitos[posicao];
	for(int i = 1;i<=limite;i++){
		int nxt = vaipara[idx][i];
		if(nxt != -1) ans += solve(posicao+1,nxt, (flag) && (i == limite) );
	}
	return dp[posicao][idx][flag] = ans;
}

ll calcula(int idx,ll limite){
	digitos.clear();
	if(limite == 0) return 0;
	iteracao++;
	ll copia = limite;
	while(copia != 0){
		digitos.push_back(copia % 10);
		copia /= 10;
	}
	tamanho = digitos.size();
	reverse(digitos.begin(),digitos.end());
	ll tot = 0;
	for(int i = 0;i<tamanho;i++){
		tot += solve(i,idx,i == 0);
	}
	return tot;
}

ll produto_fixo(int idx){
	ll inferior = A/numero[idx];
	if(A % numero[idx] != 0) inferior += 1;
	ll superior = B/numero[idx];
	if(inferior > superior) return 0LL;
	return calcula(idx,superior) - calcula(idx,inferior - 1);
}

void constroi(int idx){
	int davez = numero[idx];
	for(int i = 1;i<=9;i++){
		if(davez % i != 0){
			vaipara[idx][i] = -1;
		}
		else{
			vaipara[idx][i] = conversao[davez/i];
		}
	}
}

int main(){
	cin >> A >> B;
	raizB = (int)floor(sqrt(B));
	brute(1);
	for(int i = 1;i<=conversao.size();i++) constroi(i);
	ll total = 0;
	for(int i = 1;i<=conversao.size();i++) total += produto_fixo(i);
	cout << total << endl;
	return 0;
}