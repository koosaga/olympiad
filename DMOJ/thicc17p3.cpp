// Ivan Carvalho
// Solution to https://dmoj.ca/problem/thicc17p3
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
vector<ii> eita[1000001];
int N,Q,dia;
bool compara(ii A,ii B){
	return A.first > B.first;
}
int main(){
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		int p;
		scanf("%d",&p);
		eita[i].push_back(ii(0,p));
	}
	scanf("%d",&Q);
	for(int agora = 0;agora < Q;agora++){
		char op;
		int x,y;
		scanf(" %c %d %d",&op,&x,&y);
		if(op == 'C'){
			dia++;
			eita[x].push_back(ii(dia,y));
		}
		else{
			int resp = (*lower_bound(eita[x].rbegin(),eita[x].rend(),ii(y,Q),compara)).second;
			printf("%d\n",resp);
		}
	}
	return 0;
}