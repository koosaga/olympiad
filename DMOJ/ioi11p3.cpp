// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi11p3
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MAXN = 100010;
ll vetor[MAXN],soma[MAXN],resp,ini,fim,mediana,custo,orcamento,n;
void calcula_mediana(){
	mediana = (ini+fim)/2;
}
void calcula_custo(){
	ll temp = 0;
	ll lo,hi;
	if(mediana-1>=ini){
		lo = ini;
		hi = mediana-1;
		temp += (hi-lo+1)*vetor[mediana];
		temp -= (soma[hi] - soma[lo-1]); 
	}
	if(mediana + 1 <= fim){
		lo = mediana+1;
		hi = fim;
		temp += soma[hi] - soma[lo-1];
		temp -= (hi-lo+1)*vetor[mediana];
	}
	custo = temp;
}
int besthub(int R,int L,int X[],long long B){
	n = R;
	orcamento = B;
	for(ll i=1;i<=n;i++) vetor[i] = X[i-1];
	for(ll i=1;i<=n;i++) soma[i] = soma[i-1] + vetor[i];
	ini = 1;
	fim = 1;
	resp = 1;
	for(fim=2;fim<=n;fim++){
		calcula_mediana();
		calcula_custo();
		while(custo > orcamento){
			ini++;
			calcula_mediana();
			calcula_custo();
		}
		resp = max(resp,fim - ini + 1);
	}	
	return (int)resp;
}

int main(){
    return 0;
}
