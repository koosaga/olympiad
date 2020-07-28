// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c6p3
#include <bits/stdc++.h>
using namespace std;
vector<int> resp,organizado;
int vetor[101],resto[101],n;
int checa(int m){
	if(m == 1) return 0; 
	for(int i=1;i<=n;i++) resto[i] = vetor[i] % m;
	for(int i=2;i<=n;i++) if(resto[i] != resto[i-1]) return 0;
	return 1;
}
int main(){
	int limite = 1e9;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor[i]);
	}
	for(int i=2;i<=n;i++) limite = min(abs(vetor[i] - vetor[i-1]),limite);
	for(int m1 = 1;(m1-1)*(m1-1)<=limite;m1++){
	    if(limite % m1 != 0) continue;
		if(checa(m1)) resp.push_back(m1);
		if(checa(limite / m1)) resp.push_back(limite / m1);
	}
	sort(resp.begin(),resp.end());
	for(int i : resp){
		while(!organizado.empty() && organizado.back() == i) organizado.pop_back();
		organizado.push_back(i);
	}
	for(int i : organizado) printf("%d ",i);
	printf("\n");
	return 0;
}