// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi14p4
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

const int MAXN = 3*1e5 + 10;
const ll MOD = 1e9 + 9;

ll binary_expo(ll x,ll y,ll z){
	ll ans = 1 % z,pot = x;
	for(ll i = 0;(1LL << i) <= y;i++){
		if(y & (1LL << i)) ans = (ans*pot) % MOD;
		pot = (pot*pot) % MOD; 
	}
	return ans;
}

int valid(int n, int inputSeq[]){
	int menor = inputSeq[0];
	vector<int> tudo;
	deque<int> truque;
	for(int i  = 0;i<n;i++){
		menor = min(menor,inputSeq[i]);
		if(inputSeq[i] <= n) truque.push_back(inputSeq[i]);
		else truque.push_back(n+1);
		tudo.push_back(inputSeq[i]);
	}
	if(menor < 1) return 0;
	sort(tudo.begin(),tudo.end());
	for(int i = 0;i+1<n;i++){
		if(tudo[i] == tudo[i+1]) return 0;
	}
	if(menor > n) return 1;
	while(truque.front() != menor){
		truque.push_back(truque.front());
		truque.pop_front();
	}
	for(int i = 0;i<truque.size();i++){
		if(truque[i] <= n && truque[i] - menor != i) return 0;
	}
	return 1;
}

int replacement(int n, int gondolaSeq[], int replacementSeq[]){
	int minimo = gondolaSeq[0],maximo = gondolaSeq[0];
	deque<int> truque;
	truque.push_back(gondolaSeq[0]);
	for(int i = 1;i<n;i++){
		truque.push_back(gondolaSeq[i]);
		minimo = min(minimo,gondolaSeq[i]);
		maximo = max(gondolaSeq[i],maximo);
	}
	while(truque.front()!=minimo){
		truque.push_back(truque.front());
		truque.pop_front();
	}
	int tot = maximo - n;
	vector<ii> tudo;
	if(minimo <= n){
		int qtd = truque.front() - 1;
		while(qtd--){
			truque.push_front(truque.back());
			truque.pop_back();
		}
	}
	int mx = n,ptr = 0;
	for(int i = 0;i<n;i++){
		if(truque[i] > n) tudo.push_back(ii(truque[i],i+1));
	}
	sort(tudo.begin(),tudo.end());
	for(int i = 0;i<tudo.size();i++){
		mx++;
		replacementSeq[ptr++] = tudo[i].second;
		for(int j = mx;j<tudo[i].first;j++) replacementSeq[ptr++] = j;
		mx = tudo[i].first;
	}
	return tot;
}

int countReplacement(int n, int inputSeq[]){
	ll ans = 1;
	if(valid(n,inputSeq) == 0) return 0;
	vector<int> trocas;
	for(int i = 0;i<n;i++){
		if(inputSeq[i] > n) trocas.push_back(inputSeq[i]);
	}
	if(trocas.empty()) return 1;
	if(trocas.size() == n) ans *= n;
	trocas.push_back(n);
	int qtd = trocas.size() - 1;
	sort(trocas.begin(),trocas.end());
	for(int i = 0;i+1<trocas.size();i++){
		int a = trocas[i] + 1;
		int b = trocas[i+1];
		ans *= binary_expo(qtd,b - a,MOD);
		ans %= MOD;
		qtd--;
	}
	return (int)ans;
}

int main(){
	int tarefa,n,entrada[MAXN],saida[MAXN];
	scanf("%d",&tarefa);
	scanf("%d",&n);
	for(int i = 0;i<n;i++) scanf("%d",&entrada[i]);
	if(tarefa <= 3){
		printf("%d\n",valid(n,entrada));
	}
	else if(tarefa <= 6){
		int r = replacement(n,entrada,saida);
		printf("%d",r);
		for(int i = 0;i<r;i++) printf(" %d",saida[i]);
		printf("\n");
	}
	else{
		printf("%d\n",countReplacement(n,entrada));
	}
	return 0;
}"%d\n",countReplacement(n,entrada));
	}
	return 0;
}