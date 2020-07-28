// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1234
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
int main(){
	char frase[50];
	while(std::cin.getline(frase,50)){
		int tamanho = strlen(frase),i,valido=1;
		for(i=0;i<tamanho;i++){
			char davez = frase[i];
			if (davez != ' '){
				if (valido){
					davez = toupper(davez);
					valido = 0;
				}
				else {
					davez = tolower(davez);
					valido = 1;
				}
			}
			printf("%c",davez);
		}
		printf("\n");
	}
	return 0;
}
