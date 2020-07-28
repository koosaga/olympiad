// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c1p1
#include <cstdio>
#include <set>
using namespace std;
int main(){
	set<int> conjunto;
	for(int i=1;i<=10;i++){
		int davez;
		scanf("%d",&davez);
		conjunto.insert(davez%42);
	}
	printf("%d\n",(int)conjunto.size());
	return 0;
}