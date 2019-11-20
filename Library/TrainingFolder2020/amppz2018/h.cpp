#include <bits/stdc++.h>
using namespace std;

int a[7], p[9];
char str[4][4];

int main(){
	for(int i=0; i<7; i++) cin >> a[i];
	for(int i=0; i<3; i++) cin >> str[i];
	iota(p, p + 9, 1);
	do{
		bool ok = true;
		if(p[0] + p[1] + p[3] + p[4] != a[3]) ok = false;
		if(p[1] + p[2] + p[4] + p[5] != a[4]) ok = false;
		if(p[3] + p[4] + p[6] + p[7] != a[5]) ok = false;
		if(p[4] + p[5] + p[7] + p[8] != a[6]) ok = false;
		int sum[3] = {};
		for(int i=0; i<9; i++){
			sum[str[i/3][i%3] - 'A'] += p[i];
		}
		if(sum[0] != a[0] || sum[1] != a[1] || sum[2] != a[2]) ok = false;
		if(ok){
			for(int i=0; i<9; i++){
				printf("%d", p[i]);
				if(i % 3 == 2) puts("");
			}
			exit(0);
		}
	}while(next_permutation(p, p + 9));
	puts("NIE");
}
