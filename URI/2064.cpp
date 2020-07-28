// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2064
#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;
int frequencia[1000],favorita[1000],maximo,construindo,k,m,n;
char palavra[MAXN],antiga[MAXN],nova[MAXN],entrada[1000],dicio[1000];
int main(){
	scanf("%d %d %d",&k,&m,&n);
	scanf("%s",entrada);
	scanf("%s",palavra);
	for(int i=0;i<k;i++){
		favorita[entrada[i]] = 1;
	}
	for(int i=0;i<m;i++){
		frequencia[palavra[i]]++;
		construindo += favorita[palavra[i]];
	}
	maximo = construindo;
	for(int i=0;i<n;i++){
		scanf(" %c %c",&antiga[i],&nova[i]);
		int old = frequencia[antiga[i]];
		int rold = frequencia[nova[i]];
		frequencia[antiga[i]] = rold;
		frequencia[nova[i]] = old;
		construindo += old * (favorita[nova[i]] - favorita[antiga[i]]);
		construindo += rold * (favorita[antiga[i]] - favorita[nova[i]]);
		maximo = max(maximo,construindo);
		//printf("%c %c %d %d\n",antiga[i],nova[i],construindo,maximo);
	}
	for(char caractere = 'a';caractere <= 'z';caractere++){
		dicio[caractere] = caractere;
		frequencia[caractere] = 0;
	}
	construindo = 0;
	for(int i=0;i<m;i++){
		frequencia[palavra[i]]++;
		construindo += favorita[palavra[i]];
	}
	if(construindo == maximo){
		printf("%d\n",maximo);
		printf("%s\n",palavra);
		return 0;
	}
	for(int i=0;i<n;i++){
		int old = frequencia[antiga[i]];
		int rold = frequencia[nova[i]];
		frequencia[antiga[i]] = rold;
		frequencia[nova[i]] = old;
		construindo += old * (favorita[nova[i]] - favorita[antiga[i]]);
		construindo += rold * (favorita[antiga[i]] - favorita[nova[i]]);
		for(char caractere = 'a';caractere <= 'z';caractere++){
			if(dicio[caractere] == antiga[i]){
				dicio[caractere] = nova[i];
			}
			else if(dicio[caractere] == nova[i]){
				dicio[caractere] = antiga[i];
			}
		}
		if(construindo == maximo){
			printf("%d\n",maximo);
			for(int i=0;i<m;i++){
				printf("%c",dicio[palavra[i]]);
			}
			printf("\n");
			return 0;
		}
	}
	return 0;
}
