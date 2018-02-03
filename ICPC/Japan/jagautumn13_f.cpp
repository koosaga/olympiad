#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;
typedef pair<int, lint> pi;

string s;

pi solveE(int ptr);
pi solveT(int ptr);

pi solveT(int ptr){
	if(isdigit(s[ptr])){
		int e = ptr;
		while(e < s.size() && isdigit(s[e])){
			e++;
		}
		lint ans = 0;
		for(int j=e-1; j>=ptr; j--) ans = (ans * 10 + (s[j] - '0'));
		return pi(e, ans);
	}
	else{
		auto l = solveE(ptr + 1);
		return pi(l.first + 1, l.second * l.second % mod);
	}
}


pi solveE(int ptr){
	auto x = solveT(ptr);
	if(x.first + 2 <= s.size() && s[x.first] == '>' && s[x.first + 1] == '>'){
		auto y = solveE(x.first + 2);
		return pi(y.first, y.second >> min(x.second, 31ll));
	}
	else{
		return x;
	}
}

char inp[123456];

int main(){
    while(true){
        s.clear();
        fgets(inp, 123455, stdin);
        if(*inp == '#') break;
        for(int i=0; inp[i]; i++){
            if(!isspace(inp[i]) && inp[i] != 'S') s.push_back(inp[i]);
        }
        reverse(s.begin(), s.end());
        cout << solveE(0).second << endl;
    }
}
