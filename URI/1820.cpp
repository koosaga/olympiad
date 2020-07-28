// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1820
#include <cstdio>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#define CONV1 101
#define CONV2 10001
using namespace std;
int main(){
	int m,instancia = 1;
	while(scanf("%d",&m) && m){
		printf("Instancia %d\n",instancia++);
		unordered_set<int> conjunto;
		unordered_map<int,int> frequencia;
		for(int i=0;i<m;i++){
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			if(a > c) swap(a,c);
			if(a > b) swap(a,b);
			if(b > c) swap(b,c);
			conjunto.insert(a + b*CONV1 + c*CONV2);
			frequencia[a]++;
			frequencia[b]++;
			frequencia[c]++;
		}
		int ok = 1;
		for(int i=1;i<=100;i++){
			if(frequencia[i] < 4) continue;
			for(int j = i + 1;j <= 100;j++){
				if(frequencia[j] < 4) continue;
				for(int k=j+1;k<=100;k++){
					if(frequencia[k] < 4) continue;
					if(!conjunto.count(i + CONV1*j + CONV2*k)) continue;
					for(int l=k+1;l<=100;l++){
						if(frequencia[l] < 4) continue;
						if(!conjunto.count(i + CONV1*j + CONV2*l)) continue;
						if(!conjunto.count(i + CONV1*k + CONV2*l)) continue;
						if(!conjunto.count(j + CONV1*k + CONV2*l)) continue;
						printf("%d %d %d %d\n",i,j,k,l);
						ok = 0;
					}	
				}
			}
		}
		if(ok) printf("ok\n");
		printf("\n");
	}
	return 0;
}
