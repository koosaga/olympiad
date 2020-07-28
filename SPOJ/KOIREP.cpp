// Ivan Carvalho
// Solution to https://www.spoj.com/problems/KOIREP/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1010;
typedef pair<int,int> ii;
vector<ii> entrada;
deque<ii> janela;
int N,M,resp,qtd,freq[MAXN];
void add(int val){
	freq[val]++;
	if(freq[val] == 1) qtd++;
}
void remove(int val){
	freq[val]--;
	if(freq[val] == 0) qtd--;
}
int main(){
	scanf("%d %d",&N,&M);
	for(int i = 1;i<=N;i++){
		for(int j = 1;j<=M;j++){
			int x;
			scanf("%d",&x);
			entrada.push_back(ii(x,i));
		}
	}
	sort(entrada.begin(),entrada.end());
	resp = 1e9;
	for(int i = 0;i<entrada.size();i++){
		ii davez = entrada[i];
		add(davez.second);
		janela.push_back(davez);
		while(!janela.empty() && qtd == N){
			resp = min(resp,janela.back().first - janela.front().first);
			remove(janela.front().second);
			janela.pop_front();
		}
	}
	printf("%d\n",resp);
	return 0;
}