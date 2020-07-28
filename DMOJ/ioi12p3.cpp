// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi12p3
#include <cstdio>
#include <cstring>
#define MAXN 1000010
#define MAXL 22
int ancestral[MAXN][MAXL],nivel[MAXN],ultima[MAXN],ptr,n,atualizacao;
char corresponde[MAXN];
char get_letter(int x,int h){
	for(int i = MAXL-1;i>=0;i--){
		int v = ancestral[x][i];
		if(nivel[v] >= h){
			x = v;
		} 
	}
	return corresponde[x];
}
void Init(){
    nivel[0] = -1;
	ultima[0] = 0;
}
void TypeLetter(char L){
    char davez;
	davez = L;
	ultima[++atualizacao] = ++ptr;
	nivel[ptr] = nivel[ultima[atualizacao-1]]+1;
	corresponde[ptr] = davez;
	ancestral[ptr][0] = ultima[atualizacao-1];
	for(int i=1;i<MAXL;i++){
		ancestral[ptr][i] = ancestral[ancestral[ptr][i-1]][i-1];
	}
}
void UndoCommands(int U){
    int davez;
    davez = U;
	ultima[atualizacao+1] = ultima[atualizacao - davez];
	atualizacao++; 
}
char GetLetter(int P){
    int davez;
    davez = P;
    return get_letter(ultima[atualizacao],davez);
}
int main(){
	return 0;
}