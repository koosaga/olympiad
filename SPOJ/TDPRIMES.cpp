// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TDPRIMES/
#include <cstdio>
using namespace std;
int contador;
const int MAXN = 1e8 + 1;
const int MAXI = 1e4 + 1;
bool crivo[MAXN];
int main(){
	for(int i=2;i<MAXN;i++){
		if(!crivo[i]){
			contador++;
			if(contador % 100 == 1) printf("%d\n",i);
			if(i < MAXI){
				for(int j = i*i;j<MAXN;j+=i){
					crivo[j] = true;
				}
			}
		}
	}
	return 0;
} 