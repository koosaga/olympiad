// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1104
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
int main(){
	int a,b;
	while(scanf("%d %d",&a,&b) && (a||b)){	
		int c=0,d=0;
		set<int> A,B;
		for(int i=0;i<a;i++){
			int davez;
			scanf("%d",&davez);
			A.insert(davez);
		}
		for(int i=0;i<b;i++){
			int davez;
			scanf("%d",&davez);
			B.insert(davez);
		}
		set<int>::iterator it;
		for(it=A.begin();it!=A.end();it++) if (!B.count(*it)) c++;
		for(it=B.begin();it!=B.end();it++) if (!A.count(*it)) d++;
		printf("%d\n",min(c,d));
	}
	return 0;
}
