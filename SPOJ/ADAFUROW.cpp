// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAFUROW/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2*1e4 + 10;
typedef bitset<MAXN> bt;
bt linhas[MAXN];
int main(){
	int q;
	scanf("%d",&q);
	while(q--){
		char op;
		int x,y;
		scanf(" %c %d %d",&op,&x,&y);
		if(op == '+'){
			linhas[x].flip(y);
		}
		else if(op == '-'){
			linhas[x].flip(y);
		}
		else if(op == 'v'){
			bt davez = linhas[x] | linhas[y];
			printf("%d\n",(int)davez.count());
		}
		else if(op == '^'){
			bt davez = linhas[x] & linhas[y];
			printf("%d\n",(int)davez.count());
		}
		else if(op == '!'){
			bt davez = linhas[x] ^ linhas[y];
			printf("%d\n",(int)davez.count());
		}
		else{
			linhas[y].flip();
			bt davez = linhas[x] & linhas[y];
			printf("%d\n",(int)davez.count());
			linhas[y].flip();
		}
	}
	return 0;
}