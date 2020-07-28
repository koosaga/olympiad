// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DCEPC206/
#include <cstdio>
#include <cstring>
#include <set>
#include <unordered_map>
#define MAXN 1000001
#define LSOne(S) (S & (-S))
using namespace std;
typedef long long ll;
ll bit[MAXN];
int n, contador, vetor[MAXN];
void update(int idx, ll val){
	while(idx <= n){
		bit[idx] += val;
		idx += LSOne(idx);
	}
}
ll sum(int idx){
	ll answer = 0;
	while(idx > 0){
		answer += bit[idx];
		idx -= LSOne(idx);
	}
	return answer;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		set<int> conjunto;
		unordered_map<int,int> compressao;
		contador = 0;
		scanf("%d",&n);
		ll resposta = 0;
		for(int i = 1; i <= n; i++){
			scanf("%d",&vetor[i]);
			conjunto.insert(vetor[i]);
		}
		for(set<int>::iterator  it = conjunto.begin(); it != conjunto.end(); it ++){
			compressao[*it] = ++contador;
		}
		for(int i = 0; i<= n;i++) bit[i] = 0;
		for(int i = 1; i <= n; i++){
			resposta += sum(compressao[vetor[i]]-1);
			update(compressao[vetor[i]],ll(vetor[i]));
		} 
		printf("%lld\n",resposta);
	}
	return 0;
}  