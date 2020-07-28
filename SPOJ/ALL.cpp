// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ALL/
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define MAXN 100010
using namespace std;
vector<int> grafo[MAXN],nivel1,niveln1,nivel2,niveln2;
int grau1[MAXN],grau2[MAXN],atual1,atual2,n1,n2,d,meunivel1[MAXN],meunivel2[MAXN];
int main(){
	while(scanf("%d %d %d",&n1,&n2,&d) && (n1||n2||d)){
		for(int i=1;i<=n1+n2;i++){
			grafo[i].clear();
			grau1[i] = 0;
			grau2[i] = 0;
			meunivel1[i] = 0;
			meunivel2[i] = 0;
		}
		nivel1.clear();
		nivel2.clear();
		niveln1.clear();
		niveln2.clear();
		while(d--){
			int u,v;
			scanf("%d %d",&u,&v);
			grau1[v]++;
			grau2[v]++;
			grafo[u].push_back(v);
		}
		atual1 = 2;
		atual2 = 2;
		nivel1.push_back(1);
		niveln1.push_back(2);
		nivel2.push_back(2);
		niveln2.push_back(1);
		priority_queue<int> fila1,fila2;
		for(int i=1;i<=n1;i++){
			if(grau1[i] == 0){
				meunivel1[i] = 1;
				meunivel2[i] = 2;
				fila1.push(i);
				fila2.push(i);
			}
		}
		for(int i = n1+1;i <= n1+n2;i++){
			if(grau1[i] == 0){
				meunivel1[i] = 2;
				meunivel2[i] = 1;
				fila1.push(i);
				fila2.push(i);
			}
		}
		while(!fila1.empty()){
			int v = fila1.top();
			fila1.pop();
			for(int i=0;i<grafo[v].size();i++){
				int u = grafo[v][i];
				grau1[u]--;
				if(grau1[u] == 0){
					if(u <= n1){
						auto it = lower_bound(nivel1.begin(),nivel1.end(),meunivel1[v]);
						if(it == nivel1.end()){
							atual1++;
							nivel1.push_back(atual1);
							meunivel1[u] = atual1;
							fila1.push(u);
						}
						else{
							meunivel1[u] = *it;
							fila1.push(u); 
						}
					}
					else{
						auto it = lower_bound(niveln1.begin(),niveln1.end(),meunivel1[v]);
						if(it == niveln1.end()){
							atual1++;
							niveln1.push_back(atual1);
							meunivel1[u] = atual1;
							fila1.push(u);
						}
						else{
							meunivel1[u] = *it;
							fila1.push(u);
						}
					}
				}
			}
		}
		while(!fila2.empty()){
			int v = fila2.top();
			fila2.pop();
			for(int i=0;i<grafo[v].size();i++){
				int u = grafo[v][i];
				grau2[u]--;
				if(grau2[u] == 0){
					if(u <= n1){
						auto it = lower_bound(nivel2.begin(),nivel2.end(),meunivel2[v]);
						if(it == nivel2.end()){
							atual2++;
							nivel2.push_back(atual2);
							meunivel2[u] = atual2;
							fila2.push(u);
						}
						else{
							meunivel2[u] = *it;
							fila2.push(u); 
						}
					}
					else{
						auto it = lower_bound(niveln2.begin(),niveln2.end(),meunivel2[v]);
						if(it == niveln2.end()){
							atual2++;
							niveln2.push_back(atual2);
							meunivel2[u] = atual2;
							fila2.push(u);
						}
						else{
							meunivel2[u] = *it;
							fila2.push(u);
						}
					}
				}
			}
		}
		printf("%d\n",min(atual1,atual2)+1);
	}
	return 0;
}