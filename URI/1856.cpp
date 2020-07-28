// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1856
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <cmath>
#define MAXN 100010
#define MAXS 400
using namespace std;
int ultimobalde,S,n,m,meugrandevetor[MAXN];
deque<int> baldes[MAXS];
unordered_map<int,int> qualbalde;
void exibe(){
	for(int i=0;i<=ultimobalde;i++){
		for(int j=0;j<baldes[i].size();j++){
			printf("%d ",baldes[i][j]);
		}
	}
	printf("\n");
}
void calibra(){
	//exibe();
	for(int i=0;i<=ultimobalde;i++){
		while(baldes[i].size() > S){
			qualbalde[baldes[i].back()] = i+1;
			baldes[i+1].push_front(baldes[i].back());
			baldes[i].pop_back();
		}
	}
	if(!baldes[ultimobalde+1].empty()) ultimobalde++;
	//exibe();
}
void insere(int p,int e){
	int baldequevai = qualbalde[e];
	deque<int> temp;
	while(baldes[baldequevai].back() != e){
		temp.push_back(baldes[baldequevai].back());
		baldes[baldequevai].pop_back();
	}
	baldes[baldequevai].push_back(p);
	qualbalde[p] = baldequevai;
	while(!temp.empty()){
		//printf("%d ",temp.front());
		baldes[baldequevai].push_back(temp.back());
		temp.pop_back();
	}
	calibra();
}
void remove(int e){
	int baldequevai = qualbalde[e];
	deque<int> temp;
	//exibe();
	while(baldes[baldequevai].back() != e){
		temp.push_back(baldes[baldequevai].back());
		baldes[baldequevai].pop_back();
	}
	baldes[baldequevai].pop_back();
	//exibe();
	while(!temp.empty()){
		//printf("%d ",temp.front());
		baldes[baldequevai].push_back(temp.back());
		temp.pop_back();
	}
	//printf("\n");
	//exibe();
	calibra();
}
int conta(int a,int b){
	int maiorbalde = qualbalde[a];
	int menorbalde = qualbalde[b];
	if(maiorbalde < menorbalde){
		swap(a,b);
		swap(menorbalde,maiorbalde);
	}
	if(maiorbalde == menorbalde){
		//printf("Mesmo Balde\n");
		int contador = 0;
		int achamo1 = 0;
		for(int i=0;i<baldes[menorbalde].size();i++){
			if(baldes[menorbalde][i] == a){
				achamo1 = i;
				break;
			}
		}
		int achamo2 = 0;
		for(int i=0;i<baldes[menorbalde].size();i++){
			if(baldes[menorbalde][i] == b){
				achamo2 = i;
				break;
			}
		}
		if(achamo1 > achamo2) swap(achamo1,achamo2);
		return achamo2 - achamo1 - 1;
	}
	int contador = 0;
	int val1 = 0,val2 = 0;
	for(int i = menorbalde + 1; i <= maiorbalde - 1;i++){
		contador += baldes[i].size();
	}
	for(int i=0;i<baldes[menorbalde].size();i++){
		//printf("%d\n",baldes[menorbalde][i]);
		contador += val1;
		if(baldes[menorbalde][i] == b){
			val1 = 1;
		}
	}
	for(int i=baldes[maiorbalde].size()-1;i >= 0;i--){
		//printf("%d\n",baldes[maiorbalde][i]);
		contador += val2;
		if(baldes[maiorbalde][i] == a){
			val2 = 1;
		}
	}
	return contador;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int davez;
		scanf("%d",&davez);
		meugrandevetor[i] = davez;
	}
	scanf("%d",&m);
	S = sqrt(n+m);
	for(int i=0;i<n;i++){
		if(baldes[ultimobalde].size() < S){
			baldes[ultimobalde].push_back(meugrandevetor[i]);
			qualbalde[meugrandevetor[i]] = ultimobalde;
		}
		else{
			ultimobalde++;
			baldes[ultimobalde].push_back(meugrandevetor[i]);
			qualbalde[meugrandevetor[i]] = ultimobalde;
		}
	}
	while(m--){
		char op;
		scanf(" %c",&op);
		if(op == 'Q'){
			int a,b;
			scanf("%d %d",&a,&b);
			printf("%d\n",conta(a,b));
		}
		else if(op == 'I'){
			int p,e;
			scanf("%d %d",&p,&e);
			insere(p,e);
		}
		else if(op == 'R'){
			int p;
			scanf("%d",&p);
			remove(p);
			//exibe();
		}
	}
	return 0;
}
