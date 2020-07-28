// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc15s3
#include <cstdio>
#include <set>
using namespace std;
set<int> aero;
int main(){
	int n,g;
	scanf("%d %d",&g,&n);
	for(int i=1;i<=g;i++) aero.insert(i);
	int resp = 0;
	while(n--){
		int davez;
		scanf("%d",&davez);
		if((*aero.begin()) > davez){
			break;
		}
		set<int>::iterator it = prev(aero.upper_bound(davez));
		resp++;
		aero.erase(it);
	}
	printf("%d\n",resp);
	return 0;
}