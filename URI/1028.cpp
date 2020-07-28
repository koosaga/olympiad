// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1028
#include <cstdio>
#include <algorithm>
using namespace std;
int gcd(int x, int y){
	if (x<y) swap(x,y);
	if (x%y==0) return y;
	return gcd(y,x%y);
}
int main(){
	int casos;
	scanf("%d",&casos);
	while(casos--){
		int x,y;
		scanf("%d %d",&x,&y);
		printf("%d\n",gcd(x,y));
	}
	return 0;
}
