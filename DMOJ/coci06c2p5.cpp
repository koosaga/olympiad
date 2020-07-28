// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c2p5
#include <cstdio>
#include <algorithm>
using namespace std;
int matriz[401][401];
int resp,n,m;
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			scanf(" %c",&c);
			if(c == '.') matriz[i][j] = 1;
			matriz[i][j] += matriz[i][j-1];
		}
	}
	for(int cini = 1;cini<=m;cini++){
		for(int cfim = cini;cfim<=m;cfim++){
			int temp = 0,cur = 0;
			int tam1 = cfim - cini + 1; 
			for(int l = 1;l<=n;l++){
				int davez = matriz[l][cfim] - matriz[l][cini-1];
				if(davez != tam1){
					cur = 0;
				}
				else{
					cur++;
					temp = max(temp,cur);
				}
			}
			if(temp != 0) resp = max(resp, temp + tam1 );
		}
	}
	printf("%d\n",max(0,2*resp-1));
	return 0;
}