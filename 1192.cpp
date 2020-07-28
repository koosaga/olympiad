// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1192
#include <cstdio>
#include <cctype>
int main(){
	int casos;
	scanf("%d",&casos);
	while(casos--){
		char davez[4];
		scanf("%s",davez);
		int a= int(davez[0] - '1' + 1), b = int(davez[2] - '1' + 1);
		if (a==b) printf("%d\n",a*a);
		else if(toupper(davez[1])==davez[1]) printf("%d\n",b-a);
		else printf("%d\n",a+b);
	}
	return 0;
}
