// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PRIME1/
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN = (1 << 16) + 10;
const int MAXL = 1e6 + 10;
vector<int> primes;
int crivo[MAXL];
int main(){
	int meutopo = sqrt(MAXN) + 10;
	for(int i=2;i<MAXN;i++){
		if(crivo[i] == 0){
			primes.push_back(i);
			if(i > meutopo) continue;
			for(int j = i*i;j < MAXN; j += i){
				crivo[j] = 1;
			}
		}
	}
	int TC;
	scanf("%d",&TC);
	for(int tc = 1;tc <= TC;tc++){
		if(tc != 1) printf("\n");
		int a,b;
		scanf("%d %d",&a,&b);
		for(int i = a;i <= b;i++){
			crivo[i - a] = 0;
		}
		for(int p : primes){
			if(p > b) break;
			int comeco = a - (a % p);
			if(comeco < a) comeco += p;
			for(int j = comeco;j <= b;j += p){
				crivo[j - a] = 1;
			}
			if(comeco == p) crivo[p - a] = 0;
		}
		if(a == 1) crivo[0] = 1;
		for(int i = a;i <= b;i++){
			if(!crivo[i - a]) printf("%d\n",i);
		}
	}
	return 0;
} 