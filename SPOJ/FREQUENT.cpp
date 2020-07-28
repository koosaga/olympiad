// Ivan Carvalho
// Solution to https://www.spoj.com/problems/FREQUENT/
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
#include <unordered_map>
#define MAXN 100001
using namespace std;
int n,q,sqn,frequencia[MAXN],conjunto[MAXN],vetor[MAXN],maximo,mo_left,mo_right,resposta[MAXN],contador;
typedef struct mo_que{
	int left,right,idx;
}que;
que Q[MAXN];
bool func(que A, que B){
	if (A.left / sqn < B.left / sqn) return true;
	if (A.left / sqn > B.left / sqn) return false;
	return A.right < B.right;
}
void add(int i){
	conjunto[frequencia[i]]--;
	frequencia[i]++;
	conjunto[frequencia[i]]++;
	maximo = max(frequencia[i],maximo);
}
void remove(int i){
	conjunto[frequencia[i]]--;
	frequencia[i]--;
	conjunto[frequencia[i]]++;
	for(int j=maximo;j>=0;j--){
		if (conjunto[j] > 0){
			maximo = j;
			break;
		}
	}
}
void query(int i){
	for(int j=mo_right+1;j<=Q[i].right;j++) add(vetor[j]);
	for(int j=mo_left-1;j>=Q[i].left;j--) add(vetor[j]);
	for(int j= mo_right;j>Q[i].right;j--) remove(vetor[j]);
	for(int j = mo_left;j<Q[i].left;j++) remove(vetor[j]);
	mo_right = Q[i].right;
	mo_left = Q[i].left;
	resposta[Q[i].idx] = maximo;
}
int main(){
	while(scanf("%d",&n) && n){
		scanf("%d",&q);
		memset(frequencia,0,sizeof(frequencia));
		memset(conjunto,0,sizeof(conjunto));
		memset(vetor,0,sizeof(vetor));
		sqn = int(sqrt(n));
		maximo = 0;
		contador = 0;
		unordered_map<int,int> compressao;
		set<int> valores;
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
			valores.insert(vetor[i]);
		}
		for(set<int>::iterator it = valores.begin();it != valores.end();it++){
			compressao[*it] = ++contador;
		}
		for(int i=1;i<=n;i++){
			vetor[i] = compressao[vetor[i]];
		}
		for(int i=1;i<=q;i++){
			scanf("%d %d",&Q[i].left,&Q[i].right);
			Q[i].idx = i;
		}
		sort(Q+1,Q+q+1,func);
		conjunto[0] = n;
		for(int i=Q[1].left;i<=Q[1].right;i++) add(vetor[i]);
		resposta[Q[1].idx] = maximo;
		mo_left = Q[1].left;
		mo_right = Q[1].right;
		for(int i=2;i<=q;i++) query(i);
		for(int i=1;i<=q;i++) printf("%d\n",resposta[i]);
	}
	return 0;
}