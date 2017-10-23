#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
char str[22];

double solves(int x){
	if(x == 0) return 2;
	return 1 + x + 1 + hypot(x - 0.5, 1 - sqrt(0.75));
}

double solvec(int x){
	if(x == 0) return acos(0);
	double ret = 1 + x + 0.5;
	double C = x * x + ((sqrt(3) - 1) / 2) * ((sqrt(3) - 1) / 2);
	ret += sqrt(C - 0.25);
	double NA = 0.5;
	double NB = sqrt(C);
	double NC = hypot(1 - sqrt(0.75), x);
	double the2 = acos((NA * NA + NB * NB - NC * NC) / (2 * NA * NB));
	double the1 = acos(1 / (2 * NB));
	ret += (the2 - the1) * 0.5;
	return ret;
}


int main(){
	cin >> n >> str;
	double ans = 0;
	if(count(str, str + n, 'T') == n){
		ans = 2 * n + 1;
	}
	else{
		int lp = -1, rp = -1;
		for(int i=0; str[i]; i++){
			if(str[i] != 'T'){
				lp = i;
				break;
			}
		}
		for(int i=n-1; i>=0; i--){
			if(str[i] != 'T'){
				rp = i;
				break;
			}
		}
		ans += 2 * (rp - lp);
		if(str[lp] == 'C') ans += solvec(lp);
		else ans += solves(lp);
		if(str[rp] == 'C') ans += solvec(n-rp-1);
		else ans += solves(n-rp-1);
	}
	printf("%.10f\n", ans);
}
