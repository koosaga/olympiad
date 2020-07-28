// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1777
#include <cstdio>
#include <cstring>
#include <set>
#include <unordered_map>
#define MAXN 30100
#define LSOne(S) (S & (-S))
using namespace std;
set<int> conjunto;
unordered_map<int,int> compressao;
int bit[MAXN],A[MAXN],B[MAXN],C[MAXN],n,c,e,cont,TC,resp;
void update(int pos,int val){
	while(pos < cont){
		bit[pos] += val;
		pos += LSOne(pos);
	}
}
int query(int pos){
	int answer = 0;
	while(pos > 0){
		answer += bit[pos];
		pos -= LSOne(pos);
	}
	return answer;
}
int main(){
	scanf("%d",&TC);
	for(int tc=1;tc<=TC;tc++){
		conjunto.clear();
		compressao.clear();
		cont = 0;
		resp = 0;
		scanf("%d %d",&n,&c);
		for(int i=1;i<=c;i++){
			scanf("%d %d",&A[i],&B[i]);
			conjunto.insert(A[i]);
			conjunto.insert(B[i]);
		}
		scanf("%d",&e);
		for(int i=1;i<=e;i++){
			scanf("%d",&C[i]);
			conjunto.insert(C[i]);
		}
		for(auto it = conjunto.begin();it != conjunto.end();it++){
			compressao[*it] = ++cont;
		}
		cont += 10;
		memset(bit,0,sizeof(int)*(cont+2));
		for(int i=1;i<=c;i++){
			A[i] = compressao[A[i]];
			B[i] = compressao[B[i]];
			update(A[i],1);
			update(B[i]+1,-1);
		}
		for(int i=1;i<=e;i++){
			C[i] = compressao[C[i]];
			resp += int(query(C[i]) > 0);
		}
		printf("Caso #%d: %d\n",tc,resp);
	}
	return 0;
}
