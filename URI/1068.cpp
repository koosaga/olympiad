// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1068
#include <cstdio>
#include <cstring>
int main(){
	int i,tamanho;
	char frase[1010];
	while(scanf("%s",frase)!=EOF){
		int valor =1,resp=0;
		tamanho = strlen(frase);
		for(i=0;i<tamanho;i++){
			char davez = frase[i];
			if (davez=='(') resp++;
			if (davez==')') resp--;
			if (resp < 0) valor = 0;
		}
		if (valor && resp==0) printf("correct\n");
		else printf("incorrect\n");
	}
	return 0;
}
