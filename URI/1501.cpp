// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1501
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int main(){
	long n,b,aux;
	while(scanf("%ld %ld",&n,&b) != EOF){
		long zeros = 1e9;
		double digits = 0.0;
		for(long i=2;i<=n;i++){
			digits += log(i);
		}
		digits /= log(b);
		digits = ceil(digits + 1e-4);
		for(long i=2;i<=b;i++){
			if(b % i != 0) continue;
			long fatoresb = 0, fatoresn = 0;
			while(b % i == 0 && b > 0){
				fatoresb++;
				b /= i;
			}
			for(long j=i;j<=n;j*=i) fatoresn += n/j;
			zeros = min(zeros, fatoresn/fatoresb );
		}
		printf("%ld %.0lf\n",zeros,digits);
	}
	return 0;
}
