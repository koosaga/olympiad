// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2013D/
#include <cstdio>
#include <set>
#include <algorithm>
#define MAXN 100010
using namespace std;
int vetor[MAXN],a,b,c,n,f,m;
set<int> conjunto[10*MAXN];
int main(){
	scanf("%d %d",&n,&f);
	scanf("%d %d %d",&a,&b,&c);
	scanf("%d",&m);
	vetor[1] = a;
	conjunto[a].insert(1);
	for(int i=2;i<=n;i++){
		vetor[i] = (vetor[i-1]*b + c) % f; 
		conjunto[vetor[i]].insert(i);
	}
	while(m--){
		int time, casa;
		scanf("%d %d",&casa,&time);
		conjunto[vetor[casa]].erase(casa);
		conjunto[time].insert(casa);
		int horario = n, antihorario = n;
		bool achamoshorario = false, achamosantihorario = false;
		if(conjunto[time].find(casa) != conjunto[time].begin()) for(set<int>::iterator it = conjunto[time].find(casa);;){
			it--;
			int davez = *it;
			int temp = casa;
			if(temp == davez) break;
			bool flag = false;
			if(temp > davez){
				flag = true;
				swap(davez,temp);
			}
			int temphorario = davez - temp;
			int tempantihorario = n - temphorario;
			if(flag) swap(temphorario,tempantihorario);
			if(tempantihorario < antihorario){
				antihorario = tempantihorario;
				achamosantihorario = true;
				break;
			}
			if(it == conjunto[time].begin()) break;
			//printf("CASA %d DAVEZ %d CCW %d CW %d\n",temp,davez,antihorario,horario);
		}
		if(!achamosantihorario) for(set<int>::iterator it = conjunto[time].end();;){
			it--;
			int davez = *it;
			int temp = casa;
			if(temp == davez) break;
			bool flag = false;
			if(temp > davez){
				flag = true;
				swap(davez,temp);
			}
			int temphorario = davez - temp;
			int tempantihorario = n - temphorario;
			if(flag) swap(temphorario,tempantihorario);
			if(tempantihorario < antihorario){
				antihorario = tempantihorario;
				achamosantihorario = true;
				break;
			}
			if(it == conjunto[time].begin()) break;
			//printf("CASA %d DAVEZ %d CCW %d CW %d\n",temp,davez,antihorario,horario);
		}
		for(set<int>::iterator it = ++(conjunto[time].find(casa)); it != conjunto[time].end();it++){
			int davez = *it;
			int temp = casa;
			if(temp == davez) break;
			bool flag = false;
			if(temp > davez){
				flag = true;
				swap(davez,temp);
			}
			int temphorario = davez - temp;
			int tempantihorario = n - temphorario;
			if(flag) swap(temphorario,tempantihorario);
			if(temphorario < horario){
				horario = temphorario;
				achamoshorario = true;
				break;
			}
			//printf("CASA %d DAVEZ %d CCW %d CW %d\n",temp,davez,antihorario,horario);
		}
		if(!achamoshorario) for(set<int>::iterator it = conjunto[time].begin(); it != conjunto[time].find(casa);it++){
			int davez = *it;
			int temp = casa;
			if(temp == davez) break;
			bool flag = false;
			if(temp > davez){
				flag = true;
				swap(davez,temp);
			}
			int temphorario = davez - temp;
			int tempantihorario = n - temphorario;
			if(flag) swap(temphorario,tempantihorario);
			if(temphorario < horario){
				horario = temphorario;
				achamoshorario = true;
				break;
			}
		}
		printf("%d %d\n",antihorario,horario);
		vetor[casa] = time;
	}
	return 0;
}