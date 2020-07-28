// Ivan Carvalho
// Solution to https://dmoj.ca/problem/thicc17p5
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int,int> mapa;
int qtd,n,k;
ll resp;
deque<int> janela;
int main(){
	scanf("%d %d",&n,&k);
	for(int i = 1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		mapa[davez]++;
		if(mapa[davez] == 1){
			qtd++;
		}
		janela.push_back(davez);
		while(qtd >= k && !janela.empty()){
			resp += 1LL*(n - i + 1);
			int j = janela.front();
			janela.pop_front();
			if(mapa[j] == 1){
				qtd--;
			}
			mapa[j]--;
		}
	}
	printf("%lld\n",resp);
	return 0;
}