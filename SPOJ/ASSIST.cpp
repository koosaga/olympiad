// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ASSIST/
#include <cstdio>
#include <vector>
#define MAXN 33819
using namespace std;
int processado[MAXN];
vector<int> sortudo;
int main(){
	for(int i=2;i<MAXN;i++){
		if(!processado[i]){
			processado[i] = 1;
			//printf("%d ",i);
			sortudo.push_back(i);
			int validos = 0;
			for(int j = i;j <MAXN;j++){
				if(!processado[j]){
					validos++;
					if(validos % i == 0){
						//printf("%d ",j);
						processado[j] = 1;
					}
				}
			}
			//printf("\n");
		}
	}
	int n;
	while(scanf("%d",&n) && n){
		printf("%d\n",sortudo[n-1]);
	}
	return 0;
}