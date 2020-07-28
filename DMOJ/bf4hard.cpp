// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bf4hard
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
int freq[2010];
int esperado[2010];
char W[1000010],S[1000010];
int m,n;
int correto;
void add(char c){
	freq[c]++;
	if(freq[c] == esperado[c]){
		correto++;
	}
	else if(freq[c] == esperado[c] + 1){
		correto--;
	}
}
void remove(char c){
	freq[c]--;
	if(freq[c] == esperado[c]){
		correto++;
	}
	else if(freq[c] == esperado[c] - 1){
		correto--;
	}
}
int checa(int comeco){
	for(int i = comeco,j = 0;j < m;i++,j++){
		if(W[j] != S[i]){
			return 0;
		}
	}
	return 1;
}
int main(){
	set<char> conjunto;
	scanf("%s",S);
	scanf("%s",W);
	n = strlen(S);
	m = strlen(W);
	for(int i=0;i<m;i++){
		conjunto.insert(W[i]);
		esperado[W[i]]++;
	}
	correto = 26 - (int)conjunto.size();
	for(int i=0;i<m;i++){
		add(S[i]);
	}
	if(correto == 26 && checa(0)){
		printf("0\n");
		return 0;
	}
	for(int i = m;i<n;i++){
		remove(S[i-m]);
		add(S[i]);
		if(correto == 26 && checa(i-m+1)){
			printf("%d\n",i-m+1);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}