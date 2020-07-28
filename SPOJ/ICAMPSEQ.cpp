// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ICAMPSEQ/
#include <cstdio>
#include <algorithm>
using namespace std;
int main(){
	double a[6];
	int n;
	scanf("%d",&n);
	double minimos[16];
	double maximos[16];
	for(int bitmask = 0;bitmask<8;bitmask++){
		minimos[bitmask] = (1LL<<34);
		maximos[bitmask] = -minimos[bitmask];
	}
	for(int vez=0;vez<n;vez++){
		scanf("%lf %lf %lf %lf",&a[0],&a[1],&a[2],&a[3]);
		for(int bitmask=0;bitmask<8;bitmask++){
			double qtd = a[0];
			for(int i =0;i<3;i++){
				if(bitmask & (1<<i)) qtd+=a[i+1];
				else qtd -= a[i+1];
			}
			minimos[bitmask] = min(minimos[bitmask],qtd);
			maximos[bitmask] = max(maximos[bitmask],qtd);
		}
	}
	double ans = 0.0;
	for(int bitmask=0;bitmask<8;bitmask++){
		ans = max(ans,maximos[bitmask]-minimos[bitmask]);
	}
	printf("%.3lf\n",ans);
	return 0;
}