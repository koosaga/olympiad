// Ivan Carvalho
// Solution to https://dmoj.ca/problem/set
#include <cstdio>
#include <set>
using namespace std;
int main(){
	set<int> c;
	int n,d;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&d);
		c.insert(d);
	}
	printf("%lu\n",c.size());
	return 0;
}