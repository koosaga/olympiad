// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi98p1
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef pair<ii, vector<int> > ivctr;
vector<iii> resp;
vector<int> frequencias;
vector< ivctr > grande;
int vetor[2000010],truque[2000010],N,n,a,b,last;
int freq[21][1048581];
void solve(int k){
	int qtd = 0;
	for(int i=0;i<k;i++){
		qtd += (1<<i)*vetor[i];
	}
	freq[k][qtd]++;
	for(int i = k;i<n;i++){
		qtd -= vetor[i-k];
		qtd >>= 1;
		qtd += (1<<(k-1))*vetor[i];
		freq[k][qtd]++;
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b >> N;
	string entrada;
	cin >> entrada;
	entrada.pop_back();
	n = entrada.size();
	for(int i=0;i<n;i++) vetor[i] = (entrada[i] == '1');
	for(int i=a;i<=b;i++) solve(i);
	for(int i=a;i<=b;i++){
		for(int valor = 0;valor < (1 << i);valor++){
			int aparece = freq[i][valor];
			if(aparece == 0) continue;
			resp.push_back(MP(aparece,MP(i,valor)));
			if(truque[aparece] == 0){
				truque[aparece] = 1;
				frequencias.push_back(aparece);
			}
		}
	}
	sort(resp.begin(),resp.end());
	sort(frequencias.begin(),frequencias.end());
	int limite = 0;
	int custo = N;
	for(vector<int>::reverse_iterator it = frequencias.rbegin();it != frequencias.rend() && custo > 0;it++){
		limite = *it;
		custo--;
		//printf("%d %d\n",*it,custo);
	}
	//printf("%d\n",limite);
	for(int i=resp.size()-1;i>=0;i--){
		vector<int> exibir;
		if(resp[i].first < limite) break;
		int temp = resp[i].second.second;
		for(int j=0;j<resp[i].second.first;j++){
			exibir.push_back(temp & 1);
			temp >>= 1;
		}
		grande.push_back(MP(MP(resp[i].first,resp[i].second.first),exibir));
	}
	sort(grande.begin(),grande.end());
	int comeco = grande.size() - 1;
	for(int i=comeco;i>=0;i--){
		vector<int> exibir = grande[i].second;
		if(i == comeco){
			cout << grande[i].first.first << " ";
		}
		else if(grande[i].first.first != grande[i+1].first.first){
			cout << '\n';
			cout << grande[i].first.first << " ";
		}
		for(int j=0;j<exibir.size();j++) cout << exibir[j];
		cout << " ";
	}
	cout << '\n';
	return 0;
} << '\n';
	return 0;
}