// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c2p4
#include <bits/stdc++.h>
using namespace std;
typedef pair<char,char> dupla;
map<dupla,int> vazio;
vector<map<dupla,int> > Trie;
vector<int> fim,qtd;
int N,TriePtr;

int main(){
	fim.push_back(0);
	qtd.push_back(0);
	Trie.push_back(vazio);
	cin >> N;
	int best = 0;
	for(int palavra = 1;palavra<=N;palavra++){
		string s;
		cin >> s;
		int melhor = 1;
		int atual = 0;
		for(int i = 0, j = s.size()-1;j>=0;i++,j--){
			if(fim[atual]) melhor = max(melhor,qtd[atual]+1);
			dupla davez = dupla(s[i],s[j]);
			if(Trie[atual].count(davez)){
				atual = Trie[atual][davez];
			}
			else{
				break;
			}
		}
		if(fim[atual]) melhor = max(melhor,qtd[atual]+1);
		best = max(best,melhor);
		atual = 0;
		for(int i = 0, j = s.size()-1;j>=0;i++,j--){
			dupla davez = dupla(s[i],s[j]);
			if(Trie[atual].count(davez)){
				atual = Trie[atual][davez];
			}
			else{
				Trie[atual][davez] = ++TriePtr;
				fim.push_back(0);
				qtd.push_back(0);
				Trie.push_back(vazio);
				atual = TriePtr;
			}
		}
		fim[atual] = 1;
		qtd[atual] = max(qtd[atual],melhor);
	}
	cout << best << endl;
	return 0;
}
