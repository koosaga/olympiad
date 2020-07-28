// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco17p3
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;

const int MAXN = 2*1e5 + 10;
const int MAXL = MAXN*63;

ll X[MAXN],Y[MAXN],R[MAXN],C[MAXN],valor[MAXN],exibe[MAXN];
int logx[MAXN],logy[MAXN],tamanho[MAXN],N,Q;
int Trie[MAXL][2],TriePtr;
ll somatorio[MAXL],total[MAXN];

inline ll mod(ll val,int pot){
	return val & ((1LL << pot) - 1LL);
}

void insert(ll number,int len,ll delta){
	int atual = 1;
	for(int i =0;i<len;i++){
		int digito = (number & (1LL << i)) > 0;
		//printf("%d",digito);
		if(Trie[atual][digito]){
			atual = Trie[atual][digito];
		}
		else{
			Trie[atual][digito] = ++TriePtr;
			atual = TriePtr;
		}
	}
	//printf("\n");
	somatorio[atual] += delta;
}

ll query(ll number,int len){
	ll tot = 0;
	int atual = 1;
	for(int i = 0;i<len && atual != 0;i++){
		int digito = (number & (1LL << i)) > 0;
		//printf("%d",digito);
		tot += somatorio[atual];
		atual = Trie[atual][digito];
	}
	//printf("\n");
	return tot;
}

void build(vector<ii> insertions, vector<ii> queries  ){
	sort(insertions.begin(),insertions.end());
	sort(queries.begin(),queries.end());
	//for(ii par : insertions){
	//	printf("(%lld,%lld) ",par.first,par.second);
	//}
	//printf("\n");
	//for(ii par : queries){
	//	printf("(%lld,%lld) ",par.first,par.second);
	//}
	//printf("\n");
	for(int i = 0;i<=TriePtr;i++){
		somatorio[i] = 0;
		Trie[i][0] = Trie[i][1] = 0;
	}
	TriePtr = 1;
	ll ones = 0;
	int build_ptr = 0;
	for(int i = 0;i<queries.size();i++){
		while(build_ptr < insertions.size() && queries[i].first >= insertions[build_ptr].first ){
			int id = insertions[build_ptr].second;
			//printf("Id %d Build %d\n",id,build_ptr);
			if(logy[id] == 0){
				//printf("Ones %d\n",id);
				ones += valor[id];
			}
			else{
				//printf("Inserting id %d %lld %d %lld \n",id, mod(Y[id],logy[id]),logy[id],valor[id] );
				insert(mod(Y[id],logy[id]),logy[id],valor[id]);
			}
			build_ptr++;
		}
		int id = queries[i].second;
		ll salva = ones + query(C[id],tamanho[id]);
		//printf("I %d Id %d %lld\n",i,id,salva);
		exibe[id] += salva;
	}
}

void solve(int pot){
	ll pow2 = (1LL << pot);
	vector<ii> insercoes;
	vector<ii> perguntas;
	for(int i = 1;i<=N;i++){
		if(logx[i] == pot) insercoes.push_back(ii(X[i] % pow2,i));
	} 
	if(insercoes.empty()) return;
	for(int i = 1;i<=Q;i++){
		if(R[i] >= pow2) perguntas.push_back(ii(R[i] % pow2,i));
	}
	if(perguntas.empty()) return;
	sort(insercoes.begin(),insercoes.end());
	sort(perguntas.begin(),perguntas.end());
	//for(ii par : insercoes){
	//	printf("(%lld,%lld) ",par.first,par.second);
	//}
	//printf("\n");
	//for(ii par : perguntas){
	//	printf("(%lld,%lld) ",par.first,par.second);
	//}
	//printf("\n");
	while(!insercoes.empty()){
		vector<ii> temporario1,temporario2;
		ll resto = insercoes.back().first,id = insercoes.back().second;
		temporario1.push_back(ii(Y[id],id));
		insercoes.pop_back();
		//printf("Resto %lld do Solve %d %d %d\n",resto,pot,(int)insercoes.size()+1,(int)perguntas.size());
		while(!insercoes.empty() && insercoes.back().first == resto){
			id = insercoes.back().second;
			temporario1.push_back(ii(Y[id],id));
			insercoes.pop_back();
		}
		while(!perguntas.empty() && perguntas.back().first > resto){
			perguntas.pop_back();
		}
		while(!perguntas.empty() && perguntas.back().first == resto){
			id = perguntas.back().second;
			temporario2.push_back(ii(C[id],id));
			perguntas.pop_back();
		}
		if(temporario2.empty()) continue;
		//printf("Solve %d\n",pot);
		build(temporario1,temporario2);
	}
	perguntas.clear();
}

int main(){
	scanf("%d %d",&N,&Q);
	for(int i = 1;i<=N;i++){
		scanf("%lld %lld %lld",&X[i],&Y[i],&valor[i]);
		for(int j = 0;(1LL << j) <= X[i];j++){
			logx[i] = j; 
		}
		for(int j = 0;(1LL<<j) <= Y[i];j++){
			logy[i] = j;
		}
		//printf("Logx %d Logy %d I %d\n",logx[i],logy[i],i);
	}
	for(int i = 1;i<=Q;i++){
		scanf("%lld %lld",&R[i],&C[i]);
		ll copiac = C[i];
		while(copiac != 0){
			tamanho[i]++;
			copiac >>= 1;
		}
	}
	for(int i = 0;i<=60;i++) solve(i);
	for(int i = 1;i<=Q;i++) printf("%lld\n",exibe[i]);
	return 0;
}i = 0;i<=60;i++) solve(i);
	for(int i = 1;i<=Q;i++) printf("%lld\n",exibe[i]);
	return 0;
}