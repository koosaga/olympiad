// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg15b4
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> menores,maiores,tudo;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		tudo.push_back(davez);
		if(davez < 0) menores.push_back(davez);
		if(davez > 0) maiores.push_back(davez);
	}
	sort(tudo.begin(),tudo.end());
	sort(menores.begin(),menores.end());
	sort(maiores.begin(),maiores.end());
	int alternativa = tudo[tudo.size()-1];
	if(maiores.size() == 0 && menores.size() == 0){
		printf("0\n");
		return 0;
	}
	while(!menores.empty() && menores.size() % 2 == 1) menores.pop_back();
	int resp = 1,valido = 0;
	for(int i : menores) resp *= i,valido = 1;
	for(int i : maiores) resp *= i, valido = 1;
	if(valido) alternativa = max(alternativa,resp);
	printf("%d\n",alternativa);
	return 0;
}