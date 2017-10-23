#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

char str[1000005];

bool simulate(int v, int n){
	v++;
	stack<char> stk;
	for(int i=0; i<v; i++){
		if(str[i] == 'a' || str[i] == 'i') stk.push(str[i]);
		if(str[i] == 'e'){
			if(!stk.empty() && stk.top() == 'a') stk.pop();
			else return 0;
		}
		if(str[i] == 'o'){
			if(!stk.empty() && stk.top() == 'i') stk.pop();
			else return 0;
		}
	}
	int l = n - v - stk.size();
	for(int i=v; i<v+l/2; i++) str[i] = 'a';
	for(int i=v+l/2; i<v+l; i++) str[i] = 'e';
	for(int i=v+l; i<n; i++){
		if(stk.top() == 'a') str[i] = 'e';
		else str[i] = 'o';
		stk.pop();
	}
	return 1;
}
void solve(){
	stack<char> stk;
	scanf("%s",str);
	int n = strlen(str);
	int repl = -1;
	for(int i=0; str[i]; i++){
		if(str[i] == 'a'){
			repl = i;
			stk.push('a');
		}
		if(str[i] == 'i'){
			if(!stk.empty() && stk.top() == 'i') repl = i;
			stk.push('i');
		}
		if(str[i] == 'e'){
			if(stk.size() + 1 <= n - i - 1) repl = i;
			if(!stk.empty() && stk.top() == 'a') stk.pop();
			else{
				puts("INVALID");
				return;
			}
		}
		if(str[i] == 'o'){
			if(!stk.empty() && stk.top() == 'i') stk.pop();
			else{
				puts("INVALID");
				return;
			}
		}
	}
	if(!stk.empty()){
		puts("INVALID");
		return;
	}
	if(repl == -1){
		puts("ULTIMATE");
		return;
	}
	do{
		if(str[repl] == 'a') str[repl] = 'e';
		else if(str[repl] == 'e') str[repl] = 'i';
		else if(str[repl] == 'i') str[repl] = 'o';
		else assert(0);
		if(simulate(repl, n)){
			puts(str);
			return;
		}
	}while(1);
}

int main(){
	int t;
	cin >> t;
	while(t--) solve();
}
