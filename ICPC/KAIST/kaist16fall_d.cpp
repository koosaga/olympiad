#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

void solve(int x){
	printf("%d",(x+4)/5);
	exit(0);
}
int main(){
	int x;
	cin >> x;
	x %= 100;
	if(x == 0) x = 100;
	for(int i=0; i<4; i++){
		int pos = 0;
		for(int j=0; j<5*i+5; j++){
			pos++;
			x--;
			if(x == 0) solve(pos);
		}
		for(int j=0; j<5*i+5; j++){
			pos--;
			x--;
			if(x == 0) solve(pos);
		}
	}
}
