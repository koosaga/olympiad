// Ivan Carvalho
// Solution to https://dmoj.ca/problem/vmss7wc15c1p3
#include <cstdio>
#include <algorithm>
#define MAXN 7001
using namespace std;
int crivo[MAXN],possivel[MAXN],jvalue[MAXN];
int main(){
	int n,k;
	scanf("%d %d",&n,&k);
	possivel[0] = 1;
	for(int i=2;i<=n;i++){
		if(crivo[i]) continue;
		for(int j = i*i;j<=n;j+=i) crivo[j] = 1;
		for(int j = i;j<=n;j++){
			if(possivel[j - i]){
				if(!possivel[j]){
					possivel[j] = 1;
					jvalue[j] = jvalue[j - i] + 1;
				}
				else{
					jvalue[j] = min(jvalue[j - i] +1,jvalue[j]);
				}
			}
		}
	}
	int resp = 0;
	for(int i=1;i<=n;i++) if(possivel[i] && jvalue[i] == k) resp++;
	printf("%d\n",resp);
	return 0;
}