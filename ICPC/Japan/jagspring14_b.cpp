#include <cstdio>
#include <cstdlib>

int d1[1005];
int d2[1005];
int d3[1005];
long long d4[1005];
long long d5[1005];
int x, y, z, a, b, c, n;

int main(){
	scanf("%d %d %d %d %d %d %d",&x,&y,&z,&a,&b,&c,&n);
	for(int i=0; i<x; i++){
		d1[abs(i - a) % n]++;
	}
	for(int i=0; i<y; i++){
		d2[abs(i - b) % n]++;
	}
	for(int i=0; i<z; i++){
		d3[abs(i - c) % n]++;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			d4[(i+j)%n] += 1ll * d1[i] * d2[j];
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			d5[(i+j)%n] += 1ll* d3[i] * d4[j];
		}
	}
	for(int i=0; i<n; i++){
		printf("%lld ",d5[i]);
	}
}