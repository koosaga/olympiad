// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1300
#include <cstdio>
int main(){
	int n;
	while(scanf("%d",&n) != EOF){
		printf("%c\n",(n%6) == 0 ? 'Y' : 'N');
	}
	return 0;
}
