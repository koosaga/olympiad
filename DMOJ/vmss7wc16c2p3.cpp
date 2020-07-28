// Ivan Carvalho
// Solution to https://dmoj.ca/problem/vmss7wc16c2p3
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int vetor[1000010];
int compressao[1000010];
int main(){
	int contador = 0,n,m;
	vector<int> lis;
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&vetor[i]);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		compressao[davez] = i;
	}
	for(int i=1;i<=m;i++){
		int davez = vetor[i];
		if (compressao[davez] == 0) continue;
		davez = compressao[davez];
		vector<int>::iterator it = lower_bound(lis.begin(),lis.end(),davez);
		if (it == lis.end()) lis.push_back(davez);
		else *it = davez; 
	}
	printf("%d\n",int(lis.size()));
	return 0;
}