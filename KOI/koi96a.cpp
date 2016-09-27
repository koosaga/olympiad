#include <cstdio>
int automata[10][2]={{1,3},{9,2},{1,3},{4,9},{5,9},{5,6},{1,7},{8,7},{5,2},{9,9}};
int main(){
	char str[1000];
	int pos=0;
	while (scanf("%s",str)!=EOF) {
		pos=0;
		for (int i=0; str[i]; i++) {
			pos=automata[pos][str[i]-'0'];
		}
		printf(pos==2 || pos==6 ? "SUBMARINE":"NOISE");
		puts("");
	}
}