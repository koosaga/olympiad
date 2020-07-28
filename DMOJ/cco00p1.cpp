// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco00p1
#include <cstdio>
#include <set>
using namespace std;
set<int> grafo[28];
set<char> conjunto[28];
int existe[28];
char entrada[100];
set<char> join(set<char> A,set<char> B){
	set<char> C;
	for(set<char>::iterator it = A.begin();it != A.end();it++) C.insert(*it);
	for(set<char>::iterator it = B.begin();it != B.end();it++) C.insert(*it);
	return C;
}
set<int> join(set<int> A,set<int> B){
	set<int> C;
	for(set<int>::iterator it = A.begin();it != A.end();it++) C.insert(*it);
	for(set<int>::iterator it = B.begin();it != B.end();it++) C.insert(*it);
	return C;
}
int main(){
	int N;
	scanf("%d",&N);
	while(N--){
		char op1,op2;
		scanf(" %c %*s %c",&op1,&op2);
		if('a' <= op2 && op2 <= 'z'){
			int v = op1 - 'A';
			existe[v] = 1;
			conjunto[v].insert(op2);
		}
		else{
			int v = op1 - 'A';
			int u = op2 - 'A';
			existe[v] = 1;
			existe[u] = 1;
			grafo[v].insert(u);
		}
	}
	for(int vez = 1;vez<= 52;vez++){
		for(int i=0;i<=26;i++){
			for(int j=0;j<=26;j++){
				if(grafo[i].count(j)){
					grafo[i] = join(grafo[i],grafo[j]);
					conjunto[i] = join(conjunto[i],conjunto[j]);
				}
			}
		}
	}
	for(int i=0;i<=26;i++){
		if(existe[i]){
			printf("%c = {",'A' + i);
			int primeiro = 1;
			for(set<char>::iterator it = conjunto[i].begin();it != conjunto[i].end();it++){
				if(primeiro){
					primeiro = 0;
				}
				else{
					printf(",");
				}
				printf("%c",*it);
			}
			printf("}\n");
		}
	}
	return 0;
}}