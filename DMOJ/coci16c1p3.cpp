// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci16c1p3
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1e3 + 10;

string S[MAXN];
vector<char> R[MAXN];
char vai[MAXN],atual;
int vetor[MAXN],grau[MAXN],N,possivel;

int ehprefixo(int a,int b){
	if(S[a].size() >= S[b].size()) return 0;
	for(int i = 0;i<S[a].size();i++){
		if(S[a][i] != S[b][i]){
			return 0;
		}
	}
	return 1;
}

int checa(int a,int b){
	if(ehprefixo(a,b)) return 1;
	if(ehprefixo(b,a)) return 0;
	for(int i = 0;i<S[a].size() && i < S[b].size();i++){
		if(S[a][i] != S[b][i]){
			R[S[a][i]].push_back(S[b][i]);
			grau[S[b][i]]++;
			break;
		}
	}
	return 1;
}

int main(){
	atual = 'a';
	possivel = 1;
	cin >> N;
	for(int i = 1;i<=N;i++){
		cin >> S[i];
	}
	for(int i = 1;i<=N;i++){
		cin >> vetor[i];
	}
	for(int i = 1;i<=N;i++){
		for(int j = i+1;j<=N;j++){
			if(checa(vetor[i],vetor[j]) == 0){
				possivel = 0;
			}
		}
	}
	queue<char> bfs;
	for(char c = 'a';c<='z';c++){
		if(grau[c] == 0) bfs.push(c);
	}
	while(!bfs.empty()){
		char v = bfs.front();
		//cout << v << endl;
		bfs.pop();
		vai[v] = atual;
		atual++;
		for(char u : R[v]){
			grau[u]--;
			if(grau[u] == 0) bfs.push(u);
		}
	}
	for(char c = 'a';c <= 'z';c++){
		if(grau[c] != 0){
			possivel = 0;
		}
	}
	if(!possivel){
		cout << "NE" << endl;
	}
	else{
		cout << "DA" << endl;
		for(char c = 'a';c<='z';c++) cout << vai[c];
		cout << endl;
	}
	return 0;
}
