// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAGCD/
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
const int MAXP = 1e7 + 1;
const long long MOD = 1000000007;
int todos[MAXP],biggest[MAXP],minimo[MAXP],n;
int main(){
	for(int i=1;i<MAXP;i++){
		biggest[i] = i;
		minimo[i] = MAXP;
	}
	for(int i=2;i<MAXP;i++){
		if(biggest[i] == i){
			for(int j = 2*i;j<MAXP;j+=i){
				biggest[j] = i;
			}
		}
	}
	long long resp = 1LL;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		map<int,int> mapa;
		int a_i;
		scanf("%d",&a_i);
		for(int j = 0;j<a_i;j++){
			int davez;
			scanf("%d",&davez);
			while(davez > 1){
				mapa[biggest[davez]]++;
				davez /= biggest[davez];
			}
		}
		for(map<int,int>::iterator it = mapa.begin();it != mapa.end();it++){
			todos[(*it).first]++;
			minimo[(*it).first] = min(minimo[(*it).first],(*it).second);
		}
	}
	for(long long i = 2;i<MAXP;i++){
		if(todos[i] == n){
			while(minimo[i]--){
				resp *= i;
				resp %= MOD;
			}
		}
	}
	printf("%lld\n",resp);
	return 0;
}