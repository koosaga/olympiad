// Ivan Carvalho
// Solution to https://www.spoj.com/problems/METEORS/
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef long long ll;
struct pergunta{
	int ini,fim,meio,resp,id;
	pergunta(int _ini = 0,int _fim = 0){
		ini = _ini;
		fim = _fim;
		meio = -1;
		resp = -1;
	}
};
const int MAXN = 300010;
vector<int> estados[MAXN];
vector<pergunta> P;
ll bit[MAXN];
int N,M,K,li[MAXN],ri[MAXN],ai[MAXN],qtd[MAXN],maximom;
vector<int> bucket[MAXN];
void update_val(int idx,ll val){
	while(idx <= M + 1){
		bit[idx] += val;
		idx += LSOne(idx);
	}
}
void update(int a,int b,ll val){
	update_val(a,val);
	update_val(b+1,-val);
}
ll query(int idx){
	ll ans = 0;
	while(idx > 0){
		ans += bit[idx];
		idx -= LSOne(idx);
	}
	return ans;
}
void do_update(int i){
	if(li[i] <= ri[i]){
		update(li[i],ri[i],ai[i]);
	}
	else{
		update(li[i],M,ai[i]);
		update(1,ri[i],ai[i]);
	}
}
void checa(int i){
	ll tot = qtd[i];
	for(int j : estados[i]){
		tot -= query(j);
		if(tot <= 0) break;
	}
	if(tot <= 0){
		P[i].resp = P[i].meio;
		P[i].fim = P[i].meio - 1;
	}
	else{
		P[i].ini = P[i].meio + 1;
	}
}
int main(){
	pergunta dummy(0,0);
	P.push_back(dummy);
	scanf("%d %d",&N,&M);
	for(int i = 1;i<=M;i++){
		int x;
		scanf("%d",&x);
		estados[x].push_back(i);
	}
	for(int i = 1;i<=N;i++) scanf("%d",&qtd[i]);
	scanf("%d",&K);
	for(int i = 1;i<=N;i++){
		pergunta davez(1,K);
		P.push_back(davez);
	}
	for(int i = 1;i<=K;i++){
		scanf("%d %d %d",&li[i],&ri[i],&ai[i]);
	}
	int limite = ceil(log(K)/log(2)) + 1;
	for(int iteracao = 1;iteracao<=limite;iteracao++){
		for(int i = 1;i<=M+1;i++) bit[i] = 0;
		maximom = 0;
		for(int i = 1;i<=N;i++){
			if(P[i].ini > P[i].fim){
				continue;
			}
			P[i].meio = (P[i].ini + P[i].fim)/2;
			maximom = max(P[i].meio,maximom);
			bucket[P[i].meio].push_back(i);
		}
		for(int atualizacao = 1;atualizacao<=maximom;atualizacao++){
			do_update(atualizacao);
			if(bucket[atualizacao].empty()) continue;
			while(!bucket[atualizacao].empty()){
				int i = bucket[atualizacao].back();
				bucket[atualizacao].pop_back();
				checa(i);
			}
		}
	}
	for(int i = 1;i<=N;i++){
		if(P[i].resp == -1) printf("NIE \n");
		else printf("%d\n",P[i].resp);
	}
	return 0;
}