// Ivan Carvalho
// Solution to https://www.spoj.com/problems/FREQ2/
// Ivan Carvalho
// Pedras - Seletiva IOI - OBI 2015
#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;
typedef struct mo_que{
	int left,right,idx;
}que;
unordered_map<int,int> compressao;
int frequencia[MAXN],vetor[MAXN],resposta[MAXN],conjunto[MAXN],mo_left,mo_right,contador,n,sqn,q,maximo;
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
	scanf("%d %d",&n,&q);
	sqn = int(sqrt(n));
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		if (compressao.count(davez)){
			vetor[i] = compressao[davez];
		}
		else{
			vetor[i] = compressao[davez] = ++contador;
		}
	}
	for(int i=1;i<=q;i++){
		scanf("%d %d",&Q[i].left,&Q[i].right);
		Q[i].left++;
		Q[i].right++;
		if (Q[i].left > Q[i].right) swap(Q[i].left,Q[i].right);
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
	return 0;
}