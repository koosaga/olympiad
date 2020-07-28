// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c2p1
#include <cstdio>
#include <algorithm>
using namespace std;
int main(){
	int V[4];
	scanf("%d %d %d %d",&V[0],&V[1],&V[2],&V[3]);
	sort(V,V+4);
	printf("%d\n",V[0]*V[2]);
	return 0;
}