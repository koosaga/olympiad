// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c5p6
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 30001;
string s1[MAXN],s2[MAXN];
int N,Q,exibe[MAXN][34],triePtr;
map<string,int> apareceu;
vector<int> freq,vazio;
vector<ii> ordenado;
vector<vector<int> > Trie;
int main(){
 	//teste2.assign(27,0);
	cin.tie(0);ios_base::sync_with_stdio(0);cout.tie(0);
	vazio.assign(27,0);
	cin >> N;
	for(int i = 1;i<=N;i++){
		cin >> s1[i];
		s1[i].push_back('z'+1);
		apareceu[s1[i]] = i;
	}
	cin >> Q;
	for(int i = 1;i<=Q;i++){
		cin >> s2[i];
		s2[i].push_back('z'+1);
		if(apareceu.count(s2[i])) ordenado.push_back(ii(apareceu[s2[i]],i));
		else ordenado.push_back(ii(N,i));
	}
	sort(ordenado.begin(),ordenado.end());
	int balde = (int)ceil(sqrt(N));
	for(int lo = 1;lo<=N;lo+=balde){
		int hi = lo + balde - 1;
		triePtr = 0;
		Trie.clear();freq.clear();
		Trie.push_back(vazio);freq.push_back(0);
		int atualordenado = lo-1;
		for(int sweep = 0;sweep<Q;sweep++){
			int atualdavez = ordenado[sweep].first, idx = ordenado[sweep].second;
			if(atualdavez < lo) continue;
			while(atualordenado < atualdavez){
				atualordenado++;
				//string exibicao;
				if(atualordenado < lo || atualordenado > hi) continue;
				int atual = 0;
				for(int i = 0;i<s1[atualordenado].size();i++){
					char c = s1[atualordenado][i] - 'a';
					//exibicao.push_back(c);
					freq[atual]++;
					if(Trie[atual][c]){
						atual = Trie[atual][c];
					}
					else{
						Trie[atual][c] = ++triePtr;
						Trie.push_back(vazio);freq.push_back(0);
						atual = triePtr;
					}
				}
				freq[atual]++;
				//cout << "!" << exibicao << endl;
			}
			//cout << "?" << s2[idx] << endl;
			int atual = 0;
			for(int i = 0;i<s2[idx].size();i++){
				char c = s2[idx][i] - 'a';
				if(Trie[atual][c]){
					//cout << c << " " << freq[atual] - freq[Trie[atual][c]] << endl;
					exibe[idx][i] += (freq[atual] - freq[Trie[atual][c]]);
					atual = Trie[atual][c];
				}
				else{
					//cout << c << " " << freq[atual] << endl;
					exibe[idx][i] += freq[atual];
					break;
				}
			}
		}
	}
	for(int i = 1;i<=Q;i++){
		int resposta = 0;
		if(apareceu.count(s2[i])) resposta += s2[i].size();
		for(int j = 0;j<s2[i].size();j++){
			resposta += (exibe[i][j])*(j+1);
		}
		printf("%d\n",resposta);
	}
	return 0;
}
	}
	return 0;
}