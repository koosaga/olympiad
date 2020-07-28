// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1891
#include <cstdio>
#include <vector>
#include <set>
#define MAXN 100010
using namespace std;
int descartado[MAXN],estado[MAXN],TC,n;
char entrada[MAXN];
set<int> possiveis,alternativos;
void shuffle(int x){
	if(x < 0) return;
	if(x >= n) return;
	if(descartado[x]) return;
	if(estado[x] == 1){
		estado[x] = 0;
		possiveis.erase(x);
	}
	else{
		estado[x] = 1;
		possiveis.insert(x);
	}
}
int main(){
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		scanf("%s",entrada);
		vector<int> resposta;
		possiveis.clear();
		for(int i=0;i<n;i++){
			descartado[i] = 0;
			estado[i] = int(entrada[i] == 'D');
		}
		for(int i=0;i<n;i++){
			if(estado[i] == 1){
				possiveis.insert(i);
			}
		}
		for(int i = 0; i < n;i++){
			if(possiveis.empty()){
				break;
			}
			int davez = *(possiveis.begin());
			descartado[davez] = 1;
			estado[davez] = 0;
			shuffle(davez-1);
			shuffle(davez+1);
			resposta.push_back(davez);
			possiveis.erase(davez);
		}
		if(resposta.size() == n){
			printf("Y\n");
			printf("%d",resposta[0]+1);
			for(int i=1;i<n;i++){
				printf(" %d",resposta[i]+1);
			}
			printf("\n");
		}
		else{
			printf("N\n");
		}
	}
	return 0;
}
