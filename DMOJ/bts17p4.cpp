// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bts17p4
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
vector<ii> todos;
vector<int> menores;
int N,M,J;
int checa(int t){
	menores.clear();
	for(ii d : todos){
		if(d.second <= t) menores.push_back(d.first);
	}
	sort(menores.begin(),menores.end());
	int pos = 0;
	for(int i : menores){
		if(i - pos <= J) pos = i;
	}
	if((N + 1) - pos <= J) return 1;
	return 0;
}
int main(){
	scanf("%d %d %d",&N,&M,&J);
	while(M--){
		int a,b;
		scanf("%d %d",&a,&b);
		todos.push_back(ii(a,b));
	}
	int ini = 0, fim = 1000010 , meio, resp = -1;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(checa(meio)){
			resp = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}
	printf("%d\n",resp);
	return 0;
}