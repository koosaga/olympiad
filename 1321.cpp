// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1321
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int usada[53];
int c1,c2,c3,d1,d2;
int joga(int A,int B,int C,int D,int E,int F){
	return ((A < D) + (B < E) + (C < F)) >= 2;
}
int ehvencedora(int d3){
	int resultado = 1;
	vector<int> menor;
	menor.push_back(c1);
	menor.push_back(c2);
	menor.push_back(c3);
	sort(menor.begin(),menor.end());
	do{
		vector<int> maior;
		maior.push_back(d1);
		maior.push_back(d2);
		maior.push_back(d3);
		sort(maior.begin(),maior.end());
		do{
			resultado &= joga(menor[0],menor[1],menor[2],maior[0],maior[1],maior[2]);
		}while(next_permutation(maior.begin(),maior.end()) && resultado);
	}while(next_permutation(menor.begin(),menor.end()) && resultado);
	return resultado;
}
int main(){
	while(scanf("%d %d %d %d %d",&c1,&c2,&c3,&d1,&d2) && (c1||c2||c3||d1||d2)){
		usada[c1] = usada[c2] = usada[c3] = usada[d1] = usada[d2] = 1;
		int alguma = 0;
		for(int i=1;i<=52;i++){
			if(usada[i]) continue;
			if(!ehvencedora(i)) continue;
			printf("%d\n",i);
			alguma = 1;
			break;
		}
		if(!alguma) printf("-1\n");
		usada[c1] = usada[c2] = usada[c3] = usada[d1] = usada[d2] = 0;
	}
	return 0;
}
