// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DQUERY/
#include <cstdio>
#include <cmath>
#include <set>
#include <algorithm>
#define MAXN 200010
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
using namespace std;
int n,q,sqn,mo_left,mo_right,vetor[MAXN],resposta[MAXN],conjunto[5*MAXN],tamanho;
typedef struct mo_que{
	int left,right;
	int idx;
}que;
que Q[MAXN];
bool func(que A, que B){
	if (A.left/sqn < B.left/sqn) return true;
	if (A.left/sqn > B.left/sqn) return false;
	return A.right < B.right;
}
inline void add(int i){
	conjunto[i]++;
	tamanho += (conjunto[i] == 1);
}
inline void remove(int i){
	conjunto[i]--;
	tamanho -= (conjunto[i] == 0);
}
void query(int i){
	for(int j=mo_right+1;j<=Q[i].right;j++) add(vetor[j]);
	for(int j= mo_right;j>Q[i].right;j--) remove(vetor[j]);
	for(int j=mo_left-1;j>=Q[i].left;j--) add(vetor[j]);
	for(int j = mo_left;j<Q[i].left;j++) remove(vetor[j]);
	mo_right = Q[i].right;
	mo_left = Q[i].left;
	resposta[Q[i].idx] = tamanho;
}
int main(){
	mo_right = 1;
	getint(n);
	sqn = int(sqrt(n));
	for(int i=1;i<=n;i++) getint(vetor[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		Q[i].idx = i;
		getint(Q[i].left);
		getint(Q[i].right);
	}
	sort(Q+1,Q+q+1,func);
	mo_right = Q[1].right;
	mo_left = Q[1].left;
	for(int i=mo_left;i<=mo_right;i++) add(vetor[i]);
	resposta[Q[1].idx] = tamanho;
	for(int i=2;i<=q;i++) query(i);
	for(int i=1;i<=q;i++) printf("%d\n",resposta[i]);
	return 0;
} 