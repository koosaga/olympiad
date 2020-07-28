// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1088
#include <cstdio>
#define MAXN 100100
#define LSOne(S) (S & (-S)) 
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
int bits[MAXN];
void update(int x){
	while(x<MAXN){
		bits[x]++;
		x += LSOne(x);
	}
}
int sum(int x){
	int s = 0;
	while(x>0){
		s += bits[x];
		x -= LSOne(x);
	}
	return s;
}
int main(){
	int n;
	while(1){
		int resposta = 0;
		getint(n);
		if(n==0) break;
		for(int i=0;i<=n;i++) bits[i] = 0;
		for(int i=1;i<=n;i++){
			int temp;
			getint(temp);
			update(temp);
			resposta += sum(n) - sum(temp);
			resposta = resposta & 1;
		}
		if (resposta%2==0) printf("Carlos\n");
		else printf("Marcelo\n");
	}
	return 0;
}

