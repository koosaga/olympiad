// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c5p2
#include <bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d,e,f;
	scanf("%d%*c%d%*c%d",&a,&b,&c);
	scanf("%d%*c%d%*c%d",&d,&e,&f);
	int t1 = 60*60*a + 60*b + c;
	int t2 = 60*60*d + 60*e + f;
	if(t1 == t2){
		printf("24:00:00\n");
		return 0;
	}
	int delta = (t2 - t1);
	if(delta < 0) delta += 24*60*60;
	int v1 = delta / (60*60);
	delta %= 60*60;
	int v2 = delta/60;
	delta %= 60;
	if(v1 < 10) printf("0%d:",v1);
	else printf("%d:",v1);
	if(v2 < 10) printf("0%d:",v2);
	else printf("%d:",v2);
	if(delta < 10) printf("0%d\n",delta);
	else printf("%d\n",delta);
	return 0;
}