// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1168
#include <cstdio>
#include <cstring>
int main(){
	int a,i;
	scanf("%d",&a);
	for(i=0;i<a;i++){
		char davez[110];
		scanf("%s",davez);
		int resp=0,j,tamanho = strlen(davez);
		for(j=0;j<tamanho;j++){
			char agora = davez[j];
			switch(agora){
				case '1':
					resp += 2;
					break;
				case '2':
				case '3':
				case '5':
					resp += 5;
					break;
				case '4':
					resp += 4;
					break;
				case '6':
				case '9':
				case '0':
					resp += 6;
					break;
				case '7':
					resp += 3;
					break;
				case '8':
					resp += 7;
					break;
			}
		}
		printf("%d leds\n",resp);
	}
	return 0;
}
