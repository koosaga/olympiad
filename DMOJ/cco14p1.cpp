// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco14p1
#include <cstdio>
#include <algorithm>
#define MAXN 2010
using namespace std;
int matriz[MAXN][MAXN],linear[MAXN],modos,ida[MAXN],volta[MAXN];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c;
			scanf(" %c",&c);
			matriz[i][j] = (c == '#');
		}
	}
	for(int linha = 1;linha<=n;linha++){
		for(int i=1;i<=n;i++){
			if(matriz[linha][i] == 1) linear[i]++;
			else linear[i] = 0; 
		}
		ida[1] = min(1,linear[1]);
		for(int i=2;i<=n;i++) ida[i] = min(ida[i-1] + 1, linear[i] );
		volta[n] = min(1,linear[n]);
		for(int i =  n- 1;i >= 1;i--) volta[i] = min(volta[i+1] + 1,linear[i]);
		for(int i=1;i<=n;i++) modos += min(ida[i],volta[i]);  
	}
	printf("%d\n",modos);
	return 0;
}