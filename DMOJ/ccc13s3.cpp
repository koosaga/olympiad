// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc13s3
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
set<ii> todos;
vector<ii> disputar;
int total,favorita,jogos;
void solve(int n,vi pontuacoes){
	if(n == disputar.size()){
		int minha = pontuacoes[favorita];
		for(int i=0;i<4;i++){
			if(i == favorita) continue;
			if(pontuacoes[i] >= minha) return;
		}
		total++;
		return;
	}
	int a = disputar[n].first;
	int b = disputar[n].second;
	pontuacoes[a] += 3;
	solve(n+1,pontuacoes);
	pontuacoes[a] -= 3;
	pontuacoes[b] += 3;
	solve(n+1,pontuacoes);
	pontuacoes[b] -= 3;
	pontuacoes[a] += 1;
	pontuacoes[b] += 1;
	solve(n+1,pontuacoes);
}
int main(){
	scanf("%d",&favorita);
	favorita--;
	for(int i=0;i<4;i++){
		for(int j = i+1;j<4;j++){
			todos.insert(ii(i,j));
		}
	}
	scanf("%d",&jogos);
	vi iniciais;
	for(int i=0;i<4;i++) iniciais.push_back(0);
	while(jogos--){
		int timea,timeb,sa,sb;
		scanf("%d %d %d %d",&timea,&timeb,&sa,&sb);
		timea--;timeb--;
		if(timea > timeb){
			swap(timea,timeb);
			swap(sa,sb);
		}
		todos.erase(ii(timea,timeb));
		//printf("%d %d %d %d\n",timea,timeb,sa,sb);
		if(sa > sb){
			iniciais[timea] += 3;
		}
		if(sa < sb){
			iniciais[timeb] +=3;
		}
		if(sa == sb){
			iniciais[timea]++;
			iniciais[timeb]++;
		}
		//for(int i=0;i<4;i++) printf("%d ",iniciais[i]);
		//printf("\n");
	}
	for(auto x : todos) disputar.push_back(x);
	solve(0,iniciais);
	printf("%d\n",total);
	return 0;
}
}