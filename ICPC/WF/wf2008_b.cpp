#include <bits/stdc++.h>
typedef long long lint;
using namespace std;

string line;
int coef[105];
long long D;
lint bino[105][105];

bool solve(vector<int> V, int D){
	if(V.empty()) return true;
	if(V[0] != 0) return false;
	vector<int> miboon(V.size() - 1);
	for(int i=1; i<V.size(); i++){
		for(int j=0; j<i; j++){
			miboon[j] += bino[i][j] * V[i] % D;
			miboon[j] %= D;
		}
	}
	return solve(miboon, D);
}
int main() {
	int tc  = 0;
	while(cin >> line) {
		if(line[0] == '.') break;
		long long num = -1;
		int sgn = +1;
		memset(coef, 0, sizeof coef);
		int mode = 0;
		long long cur = 1;
		for(char c : line) {
			//printf("%c %lld %d %d %lld\n", c, num, sgn, mode, cur);
			if((c == '+' or c == '-' or c == ')') and mode == 1) {
				// cur * n^num
				if(num == -1) num = 1;
				coef[num] += cur;
			}

			if(c == ')' and mode == 0) {
				coef[0] += sgn * num;

			}
			if(c == '+') {
				sgn = 1;
				num = -1;
				mode = 0;
			}else if(c == '-'){
				sgn = -1;
				num = -1;
				mode = 0;
			}else if('0' <= c && c <= '9') {
				if(num < 0) num = 0;
				num = num * 10 + c - '0';
			}else if(c == 'n') {
				mode = 1;
				if(num < 0) num = 1;
				cur = num * sgn;
				num = -1;
				sgn = 1;
			}else if(c == ')') {
				break;
			}
		}

		D = 0;
		auto it = line.find(")");
		it += 1;
		while(++it < line.size()) {
			D = D * 10 + (line[it] - '0');
		}
		vector<int> v;
		for(int i=0; i<101; i++){
			bino[i][0] = 1;
			for(int j=1; j<=i; j++){
				bino[i][j] = (bino[i-1][j] + bino[i-1][j-1]) % D;
			}
			lint x = coef[i] % D + D;
			x %= D;
			v.push_back(x);
		}
		while(!v.empty() && v.back() == 0) v.pop_back();
		printf("Case %d: %s\n", ++tc, 
				solve(v, D) ? "Always an integer" : "Not always an integer");
	}
}
