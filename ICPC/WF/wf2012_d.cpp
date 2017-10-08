#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

lint dp[105];
int n;
string s;

lint fib[105];
string wd[105];

string tracel(int x, int l){
	if(fib[x] >= l) return wd[x].substr(fib[x] - l, l);
	if(fib[x-2] >= l) return tracel(x-2, l);
	return tracel(x-1, l-fib[x-2]) + wd[x-2];
}

string tracer(int x, int l){
	if(fib[x] >= l) return wd[x].substr(0, l);
	if(fib[x-1] >= l) return tracer(x-1, l);
	return wd[x-1] + tracer(x-2, l-fib[x-1]);
}

int fail[100005];

lint overlap(int a, int b){
	int ls = s.size()-1;
	int rs = s.size()-1;
	ls = min(ls, (int)fib[min(a, 26 + a%2)]);
	rs = min(rs, (int)fib[min(b, 26)]);
	string str = tracel(min(a, 26+a%2), ls) + tracer(min(b, 26), rs);
	int p = 0;
	int ret = 0;
	for(int i=0; i<str.size(); i++){
		while(p && str[i] != s[p]) p = fail[p];
		if(s[p] == str[i]) p++;
		if(p == s.size()){
			ret++;
			p = fail[p];
		}
	}
	return ret;
}

lint f(int x){
	if(x == 0) return (s.size() == 1 && s[0] == '0');
	if(x == 1) return (s.size() == 1 && s[0] == '1');
	if(x < 50 && fib[x] < s.size()) return 0;
	if(~dp[x]) return dp[x];
	return dp[x] = f(x-1) + f(x-2) + overlap(x-1, x-2);
}

int main(){
	memset(dp, -1, sizeof(dp));
	fib[0] = fib[1] = 1;
	wd[0] = "0";
	wd[1] = "1";
	for(int i=2; i<90; i++){
		fib[i] = fib[i-1] + fib[i-2];
		if(i <= 27) wd[i] = wd[i-1] + wd[i-2];
	}
	int t = 0;
	while(~scanf("%d",&n)){
		cin >> s;
		memset(dp, -1, sizeof(dp));
		int p = 0;
		for(int i=1; i<s.size(); i++){
			while(p && s[p] != s[i]) p = fail[p];
			if(s[p] == s[i]) p++;
			fail[i+1] = p;
		}
		printf("Case %d: %lld\n", ++t, f(n));
	}
}
