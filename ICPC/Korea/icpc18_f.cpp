#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 100005;
using pi = pair<int, int>;
#define sz(v) int((v).size())

bool err(string s){
	while(s.size() > 1){
		bool opd = 0;
		for(int i=0; i+2<sz(s); i++){
			if(isalpha(s[i]) && isalpha(s[i+2]) && (
				!isalpha(s[i+1]) && s[i+1] != '(' && s[i+1] != ')')){
				s.erase(s.begin() + i + 1);
				s.erase(s.begin() + i + 1);
				opd = 1;
			}
		}
		for(int i=0; i+2<sz(s); i++){
			if(s[i] == '(' && isalpha(s[i+1]) && s[i+2] == ')'){
				s.erase(s.begin() + i);
				s.erase(s.begin() + i + 1);
				opd = 1;
			}
		}
		if(!opd) return 1;
	}
	return 0;
}

bool proper(string s){
	while(s.size() > 3){
		int opd = 0;
		for(int i=0; i+4<sz(s); i++){
			if(s[i] == '(' && s[i+4] == ')' && isalpha(s[i+1]) && isalpha(s[i+3]) && (
				!isalpha(s[i+2]) && s[i+2] != '(' && s[i+2] != ')')){
				s.erase(s.begin() + i);
				s.erase(s.begin() + i);
				s.erase(s.begin() + i);
				s.erase(s.begin() + i + 1);
				opd = 1;
			}
		}
		if(!opd) return 0;
	}
	return isalpha(s[0]) && isalpha(s[2]) && 
				(!isalpha(s[1]) && s[1] != '(' && s[1] != ')');

}
int main(){
	string s;
	while(true){
		char c = getchar();
		if(c == EOF) break;
		if(!isspace(c)) s.push_back(c);
	}
	if(err(s)) puts("error");
	else puts(proper(s) ? "proper" : "improper");
}

