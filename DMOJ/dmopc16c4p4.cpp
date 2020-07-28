// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc16c4p4
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define MAXN 100010
using namespace std;
typedef struct mo_que{
	int left,right,idx;
}que;
int vetor[MAXN],mo_left,mo_right,resp[MAXN],freq[MAXN],pares,sqn,n,q;
vector<que> Q;
bool compara(que A,que B){
	if(A.left / sqn < B.left / sqn) return true;
	if(A.left / sqn > B.left / sqn) return false;
	return A.right < B.right;
}
void add(int i){
	if(freq[i] == 0){
		freq[i]++;
	}
	else if(freq[i] % 2 == 1){
		freq[i]++;
		pares++;
	}
	else{
		freq[i]++;
		pares--;
	}
}
void remove(int i){
	if(freq[i] == 1){
		freq[i]--;
	}
	else if(freq[i] % 2 == 1){
		freq[i]--;
		pares++;
	}
	else{
		freq[i]--;
		pares--;
	}
}
void query(int i){
	for(int j = mo_right+1;j<=Q[i].right;j++) add(vetor[j]);
	for(int j = mo_left - 1;j >= Q[i].left;j--) add(vetor[j]);
	for(int j = mo_right;j > Q[i].right;j--) remove(vetor[j]);
	for(int j = mo_left;j < Q[i].left;j++) remove(vetor[j]);
	resp[Q[i].idx] = pares;
	mo_left = Q[i].left;
	mo_right = Q[i].right;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor[i]);
	}
	sqn = sqrt(n);
	scanf("%d",&q);
	for(int i=0;i<q;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		que T;
		T.idx = i;
		T.left = a;
		T.right = b;
		Q.push_back(T);
	}
	sort(Q.begin(),Q.end(),compara);
	mo_left = Q[0].left;
	mo_right = Q[0].right;
	for(int i=mo_left;i<=mo_right;i++) add(vetor[i]);
	resp[Q[0].idx] = pares;
	for(int i=1;i<q;i++) query(i);
	for(int i=0;i<q;i++) printf("%d\n",resp[i]);
	return 0;
}n 0;
}