#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using lint = long long;

int n;
char mnv[MAXN], mxv[MAXN], str[MAXN];
int hmax[MAXN], sfxmin[MAXN];

int sgn(char c){
	if(c == '0') return 0;
	if(c == '+') return 1;
	return -1;
}

lint validate(char *c){
	int csgn = 0; lint ret = 0;
	for(int i=0; i<n; i++){
		csgn += sgn(c[i]);
		if(csgn < 0){
			puts("NIE");
			exit(0);
		}
		ret += csgn;
	}
	if(csgn != 0){
		puts("NIE");
		exit(0);
	}
	return ret;
}

int main(){
	cin >> str;
	n = strlen(str);
	for(int i=0; i<n; i++){
		char c1 = str[i];
		char c2 = str[i];
		if(str[i] == '_') c1 = '-', c2 = '+';
		hmax[i + 1] = hmax[i] + sgn(c2);
	}
	int cur = hmax[n];
	memcpy(mxv, str, sizeof(str));
	memcpy(mnv, str, sizeof(str));
	for(int i=n-1; i>=0; i--){
		if(mxv[i] == '_'){
			if(cur >= 2) mxv[i] = '-', cur -= 2;
			else if(cur >= 1) mxv[i] = '0', cur -= 1;
			else mxv[i] = '+';
		}
	}
	sfxmin[n+1] = 1e9;
	for(int i=n; i; i--){
		sfxmin[i] = min(sfxmin[i + 1], hmax[i]);
	}
	int curh = 0;
	for(int i=0; i<n; i++){
		if(mnv[i] == '_'){
			if(curh - 1 + sfxmin[i+1] - hmax[i+1] >= 0) mnv[i] = '-';
			else if(curh + sfxmin[i+1] - hmax[i+1] >= 0) mnv[i] = '0';
			else mnv[i] = '+';
		}
		curh += sgn(mnv[i]);
	}
//	cout << mnv << endl;
//	cout << mxv << endl;
	lint v1 = validate(mnv);
	lint v2 = validate(mxv);
	printf("%lld %lld\n", v1, v2);
}
