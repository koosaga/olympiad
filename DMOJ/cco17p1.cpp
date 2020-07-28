// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco17p1
#include <cstdio>
#include <vector>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
vector<ii> resposta;
vector<int> inicios;
int escolhe2(int n){
	if(n % 2 == 0) return (n/2)*(n-1);
	return ((n-1)/2)*n;
}
int main(){
	int K,ini = 0,fim = 0;
	scanf("%d",&K);
	while(K != 0){
		ini = fim + 1;
		fim = ini;
		while(escolhe2(fim - ini + 2) <= K){
			fim++;
		}
		inicios.push_back(ini);
		for(int i = ini;i+1<=fim;i++) resposta.push_back(MP(i,i+1));
		resposta.push_back(MP(fim,ini));
		K -= escolhe2(fim - ini + 1); 
	}
	for(int i=0;i+1<inicios.size();i++){
		resposta.push_back(MP(inicios[i],inicios[i+1]));
	}
	printf("%d %d\n",(int)fim,(int)resposta.size());
	for(int i=0;i<resposta.size();i++){
		printf("%d %d\n",resposta[i].first,resposta[i].second);
	}
	return 0;
}