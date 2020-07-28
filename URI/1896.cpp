// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1896
#include <cstdio>
#define MAXN 21
int A[MAXN],D[MAXN],H[MAXN],n,a,d,h;
int main(){
	scanf("%d %d %d %d",&n,&a,&d,&h);
	for(int i=0;i<n;i++){
		scanf("%d %d %d",&A[i],&D[i],&H[i]);
	}
	for(int bitmask = 0;bitmask < (1 << n);bitmask++){
		int vala=0,vald=0,valh=0,total=0;
		for(int i=0;i < n; i++){
			if(bitmask & (1 << i)){
				total++;
				//printf("%d ",i);
				vala += A[i];
				vald += D[i];
				valh += H[i];
			}
		}
		//printf("\n");
		//printf("A %d D %d H %d\n",vala,vald,valh);
		if(total < 2) continue;
		if(vala == a && vald == d && valh == h){
			printf("Y\n");
			return 0;
		}
	}
	printf("N\n");
	return 0;
}
