// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1987
#include <cstdio>
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		getchar();
		int soma=0;
		for(int i=0;i<n;i++){
			char davez;
			scanf("%c",&davez);
			soma += int(davez - '1' + 1);
		}
		if (!(soma%3)) printf("%d sim\n",soma);
		else printf("%d nao\n",soma);
	}
	return 0;
}
