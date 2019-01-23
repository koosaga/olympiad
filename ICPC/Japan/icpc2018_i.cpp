#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 1005;

bitset<MAXN> basis[MAXN];
bitset<MAXN> bumonim[MAXN];
int nayana[MAXN];

int n, m;
bitset<MAXN> a[MAXN];
int dep[MAXN], ndep[MAXN][MAXN];
char str[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%s", str);
		for(int j=0; j<m; j++){
			if(str[j] == '1') a[i].set(j);
		}
	}
	for(int i=0; i<n; i++){
		bitset<MAXN> who;
		bitset<MAXN> jasin = a[i];
		who.set(i);
		for(int j=0; j<m; j++){
			if(jasin[j]){
				if(basis[j][j]){
					jasin ^= basis[j];
					who ^= bumonim[j];
				}
				else{
					basis[j] = jasin;
					bumonim[j] = who;
					break;
				}
			}
		}
		if(!jasin.any()){
			for(int j=0; j<n; j++){
				if(who[j]) dep[j] = 1;
			}
		}
	}
	for(int i=0; i<m; i++){
		if(basis[i][i] == 0) continue;
		auto vect = basis[i];
		vect.reset(i);
		bitset<MAXN> who = bumonim[i];
		bool NIE = 0;
		for(int j=i+1; j<m; j++){
			if(vect[j]){
				if(basis[j][j]){
					vect ^= basis[j];
					who ^= bumonim[j];
				}
				else{
					NIE = 1;
					break;
				}
			}
		}
		if(NIE) continue;
		for(int j=0; j<n; j++){
			if(!dep[j] && who[j]) ndep[j][i] = 1;
		}
	}
	bitset<MAXN> dep_answer;
	for(int i=m-1; i>=0; i--){
		if(basis[i][i]){
			for(int j=i-1; j>=0; j--){
				if(basis[j][i]) basis[j] ^= basis[i];
			}
			if(basis[i].count() == 1) dep_answer[i] = 1;
		}
	}
	for(int i=0; i<n; i++){
		if(dep[i]){
			for(int j=0; j<m; j++){
				if(!dep_answer[j]) putchar('+');
				else putchar('0');
			}
		}
		else{
			for(int j=0; j<m; j++){
				if(ndep[i][j]) putchar('-');
				else putchar('0');
			}
		}
		puts("");
	}
}
