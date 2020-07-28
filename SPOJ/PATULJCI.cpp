// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PATULJCI/
#include <bits/stdc++.h>
#define gc getchar_unlocked
inline void getint(int &x){
    int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
inline void print(int n){
	char buf[11];
	buf[10] = '\n';
	int i = 9;
	while (n){
		buf[i--] = n % 10 + '0';
		n /= 10;
	}
	while (buf[i] != '\n')	putchar_unlocked(buf[++i]);
}
using namespace std;
int MAXC;
int esq[300000*50],dir[300000*50],val[300000*50],raiz[500001];
int n,czinho,q,segIt;
void update(int velho,int novo,int left,int right,int x){
	if(left == right){
		val[novo] = val[velho] + 1;
		return;
	}
	val[novo] = val[velho] + 1;
	int mid = (left+right)/2;
	if(x <= mid){
		esq[novo] = ++segIt;
		dir[novo] = dir[velho];
		update(esq[velho],esq[novo],left,mid,x);
	}
	else{
		esq[novo] = esq[velho];
		dir[novo] = ++segIt;
		update(dir[velho],dir[novo],mid+1,right,x);
	}
}
int kth(int p1,int p2,int left,int right,int count){
	if(left == right){
		return left;
	}
	int mid = (left+right)/2;
	int davez = val[esq[p2]] - val[esq[p1]];
	if(count <= davez) return kth(esq[p1],esq[p2],left,mid,count);
	return kth(dir[p1],dir[p2],mid+1,right,count - davez);
}
int query(int p1,int p2,int left,int right,int x){
	if(left == right){
		return val[p2] - val[p1];
	}
	int mid = (left+right)/2;
	if(x <= mid) return query(esq[p1],esq[p2],left,mid,x);
	return query(dir[p1],dir[p2],mid+1,right,x);
}
int conta(int x,int l,int r){
	return query(raiz[l-1],raiz[r],1,MAXC,x);
}
int find_mediana(int l,int r){
	int tam = r - l + 1;
	int meio = max(tam / 2,1);
	int cand = kth(raiz[l-1],raiz[r],1,MAXC,meio);
	if(conta(cand,l,r)*2 > tam) return cand;
	if(meio - 1 >= 1) cand = kth(raiz[l-1],raiz[r],1,MAXC,meio - 1);
	if(conta(cand,l,r)*2 > tam) return cand;
	if(meio + 1 <= tam) cand = kth(raiz[l-1],raiz[r],1,MAXC,meio + 1);
	if(conta(cand,l,r)*2 > tam) return cand;
	return -1;
}
int main(){
	getint(n);
	getint(czinho);
	MAXC = czinho;
	for(int i=1;i<=n;i++){
		raiz[i] = ++segIt;
		int v;
		getint(v);
		update(raiz[i-1],raiz[i],1,MAXC,v);
	}
	getint(q);
	while(q--){
		int l,r;
		getint(l);
		getint(r);
		int resp = find_mediana(l,r);
		if(resp == -1){
			putchar_unlocked('n');
			putchar_unlocked('o');
			putchar_unlocked('\n');
		}
		else{
			putchar_unlocked('y');
			putchar_unlocked('e');
			putchar_unlocked('s');
			putchar_unlocked(' ');
			print(resp);
		}
	}
	return 0;
} 