// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg15g6
#include <bits/stdc++.h>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 2*1e5 + 10;
typedef struct mo_que{
	int idx,left,right;
}que;
que Q[MAXN];
int freq[MAXN],vetor[MAXN],resposta[MAXN],mo_left,mo_right,tamanho,n,q,sqn,m,validos,maior,segundomaior,aparece[MAXN];
double alvo,dobroalvo;
set<ii> candidatos;
bool compara(que A,que B){
	if(A.left / sqn < B.left / sqn) return true;
	if(A.left / sqn > B.left / sqn) return false;
	return A.right < B.right;
}
void checa(){
	validos = 0;
	alvo = double(tamanho)/3.0;
	dobroalvo = 2.0*alvo;
	if(maior >= dobroalvo){
		validos+=2;
	}
	else if(maior >= alvo){
		validos++;
	}
	if(segundomaior >= alvo){
		validos++;
	}
}
void add(int i){
	tamanho++;
	aparece[freq[i]]--;
	freq[i]++;
	aparece[freq[i]]++;
	if(freq[i] == maior + 1){
		maior++;
	}
	else if(freq[i] == segundomaior + 1){
		segundomaior++;
		if(segundomaior > maior) swap(segundomaior,maior);
	}
}
void remove(int i){
	tamanho--;
	aparece[freq[i]]--;
	freq[i]--;
	aparece[freq[i]]++;
	if(segundomaior == maior && maior - 1 == freq[i]){
		if(aparece[maior] == 1){
			segundomaior--;
		}
	}
	else if(maior - 1 == freq[i]){
		maior--;
	}
	else if(segundomaior  - 1 == freq[i]){
		if(aparece[segundomaior] == 0){
			segundomaior--;
		}
	}
}
void query(int i){
	for(int j = mo_right + 1;j <= Q[i].right;j++) add(vetor[j]);
	for(int j = mo_left - 1;j >= Q[i].left;j--) add(vetor[j]);
	for(int j = mo_right;j > Q[i].right;j--) remove(vetor[j]);
	for(int j = mo_left;j < Q[i].left;j++) remove(vetor[j]);
	mo_left = Q[i].left;
	mo_right = Q[i].right;
	//printf("%d %d %d %d\n",mo_left,mo_right,maior,segundomaior);
	checa();
	resposta[Q[i].idx] = (validos >= 2);
}
int main(){
	getint(n);
	getint(m);
	aparece[0] = m;
	sqn = sqrt(n);
	for(int i=1;i<=n;i++) getint(vetor[i]);
	getint(q);
	for(int i=1;i<=q;i++){
		getint(Q[i].left);
		getint(Q[i].right);
		Q[i].idx = i;
	}
	sort(Q,Q+q+1,compara);
	alvo = 1.0;
	dobroalvo = 2.0;
	for(int i = Q[1].left;i<=Q[1].right;i++) add(vetor[i]);
	mo_left = Q[1].left;
	mo_right = Q[1].right;
	//printf("%d %d %d %d\n",mo_left,mo_right,maior,segundomaior);
	checa();
	resposta[Q[1].idx] = (validos >= 2);
	for(int i=2;i<=q;i++) query(i);
	for(int i=1;i<=q;i++){
		if(resposta[i] == 1) puts("YES");
		else puts("NO");
	}
	return 0;
}");
		else puts("NO");
	}
	return 0;
}