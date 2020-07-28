// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ILKQUERY2/
#include <cstdio>
#include <set>
#include <cmath>
#include <unordered_map>
#define MAXS 400
#define MAXN 100010
using namespace std;
set<int> conjunto;
int status[MAXN],vetor[MAXN],n,q,S,blocao[MAXS][MAXN],contador;
unordered_map<int,int> compressao;
int main(){
	scanf("%d %d",&n,&q);
	S = sqrt(n);
	for(int i=0;i<n;i++){
		status[i] = 1;
		scanf("%d",&vetor[i]);
		conjunto.insert(vetor[i]);
	}
	for(set<int>::iterator it = conjunto.begin();it != conjunto.end();it++){
		compressao[*it] = contador++;
	}
	for(int i=0;i<n;i++){
		vetor[i] = compressao[vetor[i]];
		blocao[i/S][vetor[i]]++;
	}
	while(q--){
		int op;
		scanf("%d",&op);
		if (op == 0){
			int resultado  = 0;
			int davez, left, right;
			scanf("%d %d %d",&left,&right,&davez);
			if (!compressao.count(davez)){
				printf("0\n");
				continue;
			}
			davez = compressao[davez];
			int c_left = left/S, c_right = right/S;
			if (c_left == c_right){
				for(int i = left;i<=right;i++){
					if (vetor[i] == davez){
						resultado += status[i];
					}
				}
			}
			else{
				for(int i = left; i <= ((c_left+1) * S) - 1;i++){
					if (vetor[i] == davez){
						resultado += status[i];
					}
				}
				for(int i = c_left+1;i<=c_right-1;i++){
					resultado += blocao[i][davez];
				}
				for(int i = c_right*S; i <= right; i++){
					if (vetor[i] == davez){
						resultado += status[i];
					}
				}
			}
			printf("%d\n",resultado);
		}
		if (op == 1){
			int davez;
			scanf("%d",&davez);
			if (status[davez] == 0){
				status[davez] = 1;
				blocao[davez/S][vetor[davez]]++;
			}
			else{
				status[davez] = 0;
				blocao[davez/S][vetor[davez]]--;
			}
		}
	}
	return 0;
} 
