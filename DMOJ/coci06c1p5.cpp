// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c1p5
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 20;
const int MAXL = (1 << MAXN);
double matriz[MAXN][MAXN];
double prob[MAXL];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%lf",&matriz[i][j]);
			matriz[i][j] *= 0.01;
		}
	}
	prob[0] = 1.0;
	for(int vez = 0;vez < n;vez++){
		for(int i=0;i<n;i++){
			for(int bitmask = 0;bitmask < (1 << n);bitmask++){
				//printf("%d %d\n",bitmask,bitmask & (1 << i));
				if(bitmask & (1 << i) || __builtin_popcount(bitmask) != vez) continue;
				int novabitmask = bitmask | (1 << i);
				prob[novabitmask] = max(prob[novabitmask], matriz[i][vez]*prob[bitmask] );
				//printf("I %d B %d NB %d V %d : %.6lf\n",i,bitmask,novabitmask,vez,prob[novabitmask]);
			}
		}
	}
	int pot = (1 << n) - 1;
	printf("%.6lf\n",100.0*prob[pot]);
	return 0;
}