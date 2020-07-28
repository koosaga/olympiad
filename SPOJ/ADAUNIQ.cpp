// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAUNIQ/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2*1e5 + 10;
const int BUCKET = 3430;
struct que{
	int id,l,r,t;
};
struct upd{
	int pos,velho,novo;
};
int divisao[MAXN],mo_left,mo_right,mo_time,n,q,freq[MAXN],exibir[MAXN],vetor[MAXN],resp;
vector<que> Q;
vector<upd> U;
bool compara(que A,que B){
	if(divisao[A.l] != divisao[B.l]) return divisao[A.l] < divisao[B.l];
	if(divisao[A.r] != divisao[B.r]) return divisao[A.r] < divisao[B.r];
	return A.t < B.t;
}
void add(int val){
	freq[val]++;
	if(freq[val] == 1) resp++;
	else if(freq[val] == 2) resp--;
}
void remove(int val){
	freq[val]--;
	if(freq[val] == 1) resp++;
	else if(freq[val] == 0) resp--;
}
void update(int idx,int novo){
	if(mo_left <= idx && idx <= mo_right){
		remove(vetor[idx]);
		vetor[idx] = novo;
		add(vetor[idx]);
	}
	else{
		vetor[idx] = novo;
	}
}
void doQuery(int idx){
	for(int t = mo_time + 1;t <= Q[idx].t;t++) update(U[t-1].pos,U[t-1].novo);
	for(int t = mo_time;t > Q[idx].t;t--) update(U[t-1].pos,U[t-1].velho);
	for(int i = mo_right + 1;i<=Q[idx].r;i++) add(vetor[i]);
	for(int i = mo_left - 1;i>=Q[idx].l;i--) add(vetor[i]);
	for(int i = mo_right;i>Q[idx].r;i--) remove(vetor[i]);
	for(int i = mo_left;i<Q[idx].l;i++) remove(vetor[i]);
	mo_left = Q[idx].l;mo_right = Q[idx].r;mo_time = Q[idx].t;
	exibir[Q[idx].id] = resp;
}
int main(){
	scanf("%d %d",&n,&q);
	for(int i = 0;i<n;i++){
		scanf("%d",&vetor[i]);
		divisao[i] = i/BUCKET;
	}
	for(int i = 0;i<q;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		if(x == 1){
			mo_time++;
			upd davez;
			davez.pos = y;
			davez.velho = vetor[y];
			davez.novo = z;
			vetor[y] = z;
			U.push_back(davez);
			exibir[i] = -1;
		}
		else{
			que davez;
			davez.l = y;
			davez.r = z;
			davez.t = mo_time;
			davez.id = i;
			Q.push_back(davez);
		}
	}
	sort(Q.begin(),Q.end(),compara);
	for(int i = 0;i<n;i++) add(vetor[i]);
	mo_left = 0;mo_right = n-1;
	for(int i = 0;i<Q.size();i++) doQuery(i);
	for(int i = 0;i<q;i++) if(exibir[i] != -1) printf("%d\n",exibir[i]);
	return 0;
}