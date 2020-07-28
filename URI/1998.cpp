// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1998
#include <cstdio>
#include <queue>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
int vetor[600];
using namespace std;
int main(){
	int n;
	while(scanf("%d",&n) && n != -1){
		for(int i=1;i<=n;i++){
			getint(vetor[i]);
		}
		for(int i=n;i>=1;i--){
			if (vetor[i] == 0) continue;
			if (vetor[i] % i == 0){
				int val = vetor[i] / i;
				for(int j=1;j<i;j++) vetor[j] += val;
				vetor[i] = 0;
			}
		}
		bool flag = true;
		for(int i=1;i<=n && flag;i++){
			if (vetor[i] != 0){
				flag = false;
			}
		}
		printf("%c\n",flag ? 'S' : 'N');
	}
	return 0;
}
