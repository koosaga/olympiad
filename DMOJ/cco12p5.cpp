// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco12p5
#include <cstdio>
#include <cstring>
#include <cmath>
int existe[101];
int freq[101];
int main(){
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int v;
		scanf("%d",&v);
		existe[v] = 1;
	}
	for(int resp = 1;resp <= 100;resp++){
		int ok = 1;
		memset(freq,0,sizeof(freq));
		for(int i=0;i<=resp;i++){
			freq[(int)round(100.0*double(i)/double(resp))]++;
		}
		for(int i=0;i<=100;i++){
			if(existe[i] && !freq[i]) ok = 0;
		}
		if(ok){
			printf("%d\n",resp);
			return 0;
		}
	}
	return 0;
}