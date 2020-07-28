// Ivan Carvalho
// Solution to https://dmoj.ca/problem/boi2007p3
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e6 + 10;
deque<ii> minimo,maximo;
int N,M,C,existe;
int main(){
	scanf("%d %d %d",&N,&M,&C);
	for(int i = 1;i<M;i++){
	    int x;
	    scanf("%d",&x);
		ii davez = ii(x,i);
		while(!minimo.empty() && minimo.back() > davez) minimo.pop_back();
		while(!maximo.empty() && maximo.back() < davez) maximo.pop_back();
		minimo.push_back(davez);
		maximo.push_back(davez);
	}
	for(int i = M;i<=N;i++){
		int x;
	    scanf("%d",&x);
		ii davez = ii(x,i);
		while(!minimo.empty() && minimo.back() > davez) minimo.pop_back();
		while(!maximo.empty() && maximo.back() < davez) maximo.pop_back();
		minimo.push_back(davez);
		maximo.push_back(davez);
		if(minimo.front().second == i - M) minimo.pop_front();
		if(maximo.front().second == i - M) maximo.pop_front();
		if(maximo.front().first - minimo.front().first <= C){
			existe++;
			printf("%d\n",i - M + 1);
		}
	}
	if(!existe) printf("NONE\n");
	return 0;
}
