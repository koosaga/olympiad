// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c4p5
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
vector<ii> ordenado,exibir;
vector<int> compressao;
ii bit[MAXN],best;
int anterior[MAXN],n;
void update(int idx,ii val){
	while(idx < MAXN){
		bit[idx] = max(bit[idx],val);
		idx += LSOne(idx);
	}
}
ii read(int idx){
	ii ans = ii(0,-1);
	while(idx > 0){
		ans = max(bit[idx],ans);
		idx -= LSOne(idx);
	}
	return ans;
}
int main(){
	best = ii(0,-1);
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		ordenado.push_back(ii(y,-x));
		compressao.push_back(-x);
	}
	sort(ordenado.begin(),ordenado.end());
	ordenado.erase(unique(ordenado.begin(),ordenado.end()),ordenado.end());
	sort(compressao.begin(),compressao.end());
	compressao.erase(unique(compressao.begin(),compressao.end()),compressao.end());
	for(int i = 0;i < MAXN;i++) bit[i] = ii(0,-1);
	for(int i = 0;i<ordenado.size();i++){
		int tx = lower_bound(compressao.begin(),compressao.end(),ordenado[i].second) - compressao.begin() + 1;
		ii novo1 = read(tx);
		ii novo2 = ii(novo1.first + 1,i);
		anterior[i] = novo1.second;
		update(tx,novo2);
		best = max(best,novo2);
	}
	for(int i = best.second;i != -1;i = anterior[i]){
		exibir.push_back(ordenado[i]);
	}
	printf("%d\n",(int)exibir.size());
	for(ii d : exibir){
		printf("%d %d\n",-d.second,d.first);
	}
	return 0;
}