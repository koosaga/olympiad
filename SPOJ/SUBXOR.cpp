// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SUBXOR/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2*1e6 + 10;
const int MAXL = 22;
int Trie[MAXN][2],qtd[MAXN],ptr,n,k;
int binaryk[MAXL],binaryx[MAXL],xorsum;
void insert(int x){
	memset(binaryx,0,sizeof(binaryx));
	int atual = 1;
	for(int i = 0;i<MAXL;i++){
		binaryx[i] = (x & 1);
		x = (x >> 1);
	}
	//for(int i = MAXL - 1;i>=0;i--) printf("%d",binaryx[i]);
	//printf("\n");
	for(int i = MAXL - 1;i>=0;i--){
		int digit = binaryx[i];
		//printf("%d*",atual);
		if(Trie[atual][digit]){
			atual = Trie[atual][digit];
		}
		else{
			Trie[atual][digit] = ++ptr;
			atual = ptr;
		}
		qtd[atual]++;
	}
	//printf("\n");
}
int query(int x){
	memset(binaryx,0,sizeof(binaryx));
	int atual = 1;
	for(int i = 0;i<MAXL;i++){
		binaryx[i] = (x & 1);
		x = (x >> 1);
	}
	int ret = 0;
	for(int i = MAXL - 1;i>=0 && atual;i--){
		int digit = binaryx[i];
		int otherdigit = binaryk[i];
		if(otherdigit){
			if(Trie[atual][digit]) ret += qtd[Trie[atual][digit]];
			//printf("%d|",qtd[Trie[atual][digit]]);
			atual = Trie[atual][1 - digit];
		}
		else{
			//printf("0|");
			atual = Trie[atual][digit];
		}
	}
	//printf("\n");
	return ret;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		xorsum = 0;ptr = 1;
		memset(qtd,0,sizeof(qtd));memset(Trie,0,sizeof(Trie));memset(binaryk,0,sizeof(binaryk));memset(binaryx,0,sizeof(binaryx));
		for(int i = 0;i<MAXL;i++){
			binaryx[i] = binaryk[i] = 0;
		}
		scanf("%d %d",&n,&k);
		int copiak = k;
		for(int i = 0;i<MAXL;i++){
			binaryk[i] = (copiak & 1);
			copiak = (copiak >> 1);
		}
		//for(int i = MAXL - 1;i>=0;i--) printf("%d",binaryk[i]);
		//printf("\n");
		insert(xorsum);
		long long resp = 0;
		for(int i = 1;i<=n;i++){
			int davez;
			scanf("%d",&davez);
			xorsum ^= davez;
			long long delta = 1LL*query(xorsum);
			//printf("Agora foi %lld\n",delta);
			resp += delta;
			insert(xorsum);
		}
		printf("%lld\n",resp);
	}
	return 0;
}