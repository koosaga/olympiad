// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1253
#include <cstdio>
#include <cstring>
char entrada[100010];
int TC,muda;
int main(){
	scanf("%d",&TC);
	while(TC--){
		scanf("%s",entrada);
		scanf("%d",&muda);
		for(int i=0;i<strlen(entrada);i++){
			char novo = ((((entrada[i] - 'A') - muda) % 26) + 26) % 26;
			printf("%c",novo + 'A');
		}
		printf("\n");
	}
	return 0;
}
