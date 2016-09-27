#include <cstdio>
char evil[101],angel[101],search[21];
int searchFromEvil(int i,int ealoc);
int searchFromAngel(int i,int ealoc);

int e[21][101]={};
int a[21][101]={};

int searchFromEvil(int i,int ealoc){
	if(e[i][ealoc]) return e[i][ealoc];
	if(search[i]==0) return 1;
	int backup=ealoc;
	int r=0;
	while (evil[ealoc]) {
		if(evil[ealoc]==search[i]) r+=searchFromAngel(i+1, ealoc+1);
		ealoc++;
	}
	return e[i][backup]=r;
}

int searchFromAngel(int i,int ealoc){
	if(a[i][ealoc]) return a[i][ealoc];
	if(search[i]==0) return 1;
	int backup=ealoc;
	int r=0;
	while (angel[ealoc]) {
		if(angel[ealoc]==search[i]) r+=searchFromEvil(i+1, ealoc+1);
		ealoc++;
	}
	return a[i][backup]=r;
}
int main(){
	scanf("%s %s %s",search,evil,angel);
	printf("%d",searchFromEvil(0,0)+searchFromAngel(0,0));
}