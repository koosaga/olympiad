// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADANUM/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
#include <unordered_map>
#define MAXN 200010
using namespace std;
typedef long long ll;
typedef struct mo_que{
	int left,right,idx;
}que;
int n,q,sqn,mo_left,mo_right,vetor[MAXN],contador;
ll resp,resposta[MAXN],freq[MAXN],afrente[MAXN],qtd[MAXN],acumulada[MAXN],responsavel[MAXN];
que Q[MAXN];
set<int> conjunto;
unordered_map<int,int> compressao;
void add(int x){
	ll velha = freq[x];
	freq[x]++;
	ll nova = freq[x];
	resp -= responsavel[velha];
	resp -= responsavel[nova];
	qtd[velha]--;
	afrente[velha]++;
	qtd[nova]++;
	responsavel[velha] = (acumulada[afrente[velha] + qtd[velha]] - acumulada[afrente[velha]])*velha;
	responsavel[nova] = (acumulada[afrente[nova] + qtd[nova]] - acumulada[afrente[nova]])*nova;
	resp += responsavel[velha];
	resp += responsavel[nova];
}
void remove(int x){
	ll velha = freq[x];
	freq[x]--;
	ll nova = freq[x];
	resp -= responsavel[velha];
	resp -= responsavel[nova];
	qtd[velha]--;
	afrente[nova]--;
	qtd[nova]++;
	responsavel[velha] = (acumulada[afrente[velha] + qtd[velha]] - acumulada[afrente[velha]])*velha;
	responsavel[nova] = (acumulada[afrente[nova] + qtd[nova]] - acumulada[afrente[nova]])*nova;
	resp += responsavel[velha];
	resp += responsavel[nova];
}
void query(int i){
	for(int j = mo_right + 1;j <= Q[i].right;j++) add(vetor[j]);
	for(int j = mo_left - 1;j >= Q[i].left;j--) add(vetor[j]);
	for(int j = mo_right;j > Q[i].right;j--) remove(vetor[j]);
	for(int j = mo_left;j < Q[i].left;j++) remove(vetor[j]);
	mo_left = Q[i].left;
	mo_right = Q[i].right;
	//printf("%d %d\n",mo_left,mo_right);
	resposta[Q[i].idx] = resp;
}
bool func(que A,que B){
	if(A.left / sqn < B.left / sqn) return true;
	if(A.left / sqn > B.left / sqn) return false;
	return A.right < B.right;
}
int main(){
	scanf("%d %d",&n,&q);
	sqn = sqrt(n);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor[i]);
		conjunto.insert(vetor[i]);
	}
	for(set<int>::iterator it = conjunto.begin();it != conjunto.end();it++){
		compressao[*it] = ++contador;
	}
	for(int i=1;i<=n;i++){
		vetor[i] = compressao[vetor[i]];
	}
	qtd[0] = contador;
	for(ll i=1;i<=contador;i++){
		acumulada[i] = acumulada[i-1] + i;
		//printf("%lld ",acumulada[i]);
	}
	//printf("\n");
	for(int i=1;i<=q;i++){
		scanf("%d %d",&Q[i].left,&Q[i].right);
		Q[i].idx = i;
	}
	sort(Q+1,Q+q+1,func);
	mo_left = Q[1].left;
	mo_right = Q[1].right;
	//printf("%d %d\n",mo_left,mo_right);
	for(int i=mo_left;i <= mo_right;i++) add(vetor[i]);
	//printf("Qtd[0] = %lld Qtd[1] = %lld Qtd[2] = %lld\n",qtd[0],qtd[1],qtd[2]);
	//printf("afrente[0] = %lld afrente[1] = %lld afrente[2] = %lld\n",afrente[0],afrente[1],afrente[2]);
	resposta[Q[1].idx] = resp;
	for(int i=2;i<=q;i++) query(i);
	for(int i=1;i<=q;i++){
		printf("%lld\n",resposta[i]);
	}
	return 0;
}