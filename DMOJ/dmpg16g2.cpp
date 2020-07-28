// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg16g2
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

const int MAXN = 1e3 + 2;
const int MAXK = 32;

ll inter[MAXK],uniao[MAXK];
char entrada[MAXN];
ii vetor[MAXN];
int grid[MAXN][MAXN],ini[MAXN],fim[MAXN],N;

ll soma(ll x){
	return (x*(x+1))/2;
}

ll histogram(){
 
	vetor[0] = ii(-1,0);
	stack<int> pilha;
	pilha.push(0);

	for(int i = 1;i<=N;i++){
		while(!pilha.empty() && vetor[pilha.top()] > vetor[i]){
			fim[pilha.top()] = i;
			pilha.pop();
		}
		ini[i] = pilha.top();
		pilha.push(i);
	}
	while(!pilha.empty()){
		fim[pilha.top()] = N+1;
		pilha.pop();
	}

	ll ans = 0;
	for(int i = 1;i<=N;i++){
		ini[i]++;
		fim[i]--;
		int a = i - ini[i] + 1;
		int b = fim[i] - i + 1;
		ans += 1LL*a*b*vetor[i].first;
	}

	return ans;

}

ll histogram_debug(){

	ll ans = 0;
	for(int i = 1;i<=N;i++){
		int minimo = vetor[i].first;
		ans += minimo;
		for(int j = i+1;j<=N;j++){
			minimo = min(vetor[j].first,minimo);
			ans += minimo;
		}
	}

	//printf("ANS %lld\n",ans);

	return ans;

}

ll solve_uniao(int bitmask){

	if(uniao[bitmask] != -1) return uniao[bitmask];	

	for(int j = 1;j<=N;j++) vetor[j].second = j;
	memset(vetor,0,sizeof(vetor));
	ll ans = soma(N)*soma(N);

	for(int i = 1;i<=N;i++){

		for(int j = 1;j<=N;j++){
			if(bitmask & grid[i][j]) vetor[j].first = 0;
			else vetor[j].first++;
		}

		ans -= histogram();

	}

	//printf("Uniao %d com %lld\n",bitmask,ans);

	return uniao[bitmask] = ans;

}

ll solve_inter(int bitmask){

	if(inter[bitmask] != -1) return inter[bitmask];

	int cont = __builtin_popcount(bitmask);
	if(cont == 1) return inter[bitmask] = solve_uniao(bitmask);
	int cof = (cont % 2 == 0) ? (1) : (-1);

	ll ans = 0;
	for(int nbitmask = 1;nbitmask<32;nbitmask++){
		if((nbitmask & bitmask) != nbitmask) continue;
		int ncont = __builtin_popcount(nbitmask);
		int ncof = (ncont % 2 == 1) ? (1) : (-1);
		if(bitmask == nbitmask){
			ans -= solve_uniao(nbitmask);
		}
		else{
			ans += ncof*solve_inter(nbitmask);
		}
	}

	//printf("Inter %d com %lld\n",bitmask,cof*ans);

	return inter[bitmask] = cof*ans;

}

int main(){

	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		scanf("%s",entrada);
		for(int j = 1;j<=N;j++){
			char c = entrada[j-1];
			if(c == '.') continue;
			int d = c - 'A';
			grid[i][j] = (1 << d);
		}
	}

	memset(inter,-1,sizeof(inter));
	memset(uniao,-1,sizeof(inter));
	printf("%lld\n",solve_inter(31));

	return 0;

}
