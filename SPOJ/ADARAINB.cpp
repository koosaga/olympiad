// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADARAINB/
#include <cstdio>
#include <queue>
#define LSOne(S) (S & (-S))
#define MAXN 300010
#define MAXL 5010
#define MP make_pair
using namespace std;
typedef pair<int,int> i2;
typedef pair<int,i2> i3;
typedef pair<int,i3> i4;
int bit[MAXL],resp[MAXN],n,m,l;
void update(int idx,int val){
	while(idx < MAXL){
		bit[idx] += val;
		idx += LSOne(idx);
	}
}
int query(int idx){
	int ans = 0;
	while(idx > 0){
		ans += bit[idx];
		idx -= LSOne(idx);
	}
	return ans;
}
int main(){
	priority_queue<i4, vector<i4>, greater<i4> > atualizacoes;
	priority_queue<i3, vector<i3>, greater<i3> > remocoes,perguntas;
	scanf("%d %d %d",&n,&m,&l);
	for(int i =1;i <= n;i++){
		int x1,y1,x2,y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		atualizacoes.push(MP(x1,MP(x2,MP(y1,y2))));
	}
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		perguntas.push(MP(x,MP(y,i)));
	}
	while(!perguntas.empty()){
		i3 davez = perguntas.top();
		perguntas.pop();
		int x = davez.first, y = davez.second.first, id = davez.second.second;
		while(!atualizacoes.empty() && atualizacoes.top().first <= x){
			i4 atualizacao = atualizacoes.top();
			atualizacoes.pop();
			remocoes.push(atualizacao.second);
			int x1 = atualizacao.first, x2 = atualizacao.second.first, y1 = atualizacao.second.second.first, y2 = atualizacao.second.second.second;
			update(y1,1);
			update(y2 + 1,-1);
		}
		while(!remocoes.empty() && remocoes.top().first < x){
			i3 remocao = remocoes.top();
			remocoes.pop();
			int x2 = remocao.first, y1 = remocao.second.first, y2 = remocao.second.second;
			update(y1,-1);
			update(y2 + 1,1);
		}
		resp[id] = query(y);
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",resp[i]);
	}
	return 0;
}