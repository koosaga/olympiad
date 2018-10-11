#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 70005;
const int mod = 1e9 + 7;

int match[MAXN];

bool f(int s, int e, string &str){
	if(str[s] == 'S'){
		if(s + 1 < e && str[s + 1] == ','){
			return f(s + 2, e, str);
		}
		return s + 1 == e;
	}
	if(str[s] == 'B'){
		if(s + 1 < e && str[s + 1] != '(') return false;
		int new_mtch = match[s + 1];
		if(new_mtch + 1 == e){
			return f(s + 2, new_mtch, str);
		}
		if(new_mtch + 1 < e && str[new_mtch + 1] == ','){
			return f(s + 2, new_mtch, str) && f(new_mtch + 2, e, str);
		}
		return false;
	}
	return false;
}

bool valid(string s){
	stack<int> stk;
	for(auto &i : s){
		if(!isalpha(i) && i != ',' && i != '[' && i != ']' && i != '(' && i != ')'){
			return false; // condition 2
		}
		if(isalpha(i) && i != 'S' && i != 'L' && i != 'B'){
			return false; // condition 4
		}
		// condition 1
		if(i == '[') stk.push(i);
		if(i == '(') stk.push(i);
		if(i == ')'){
			if(!stk.empty() && stk.top() == '('){
				stk.pop();
			}
			else return false;
		}
		if(i == ']'){
			if(!stk.empty() && stk.top() == '['){
				stk.pop();
			}
			else return false;
		}
	}
	if(!stk.empty()) return false;
	for(auto &i : s){
		if(i == '[') i = '(';
		if(i == ']') i = ')';
		if(i == 'L') i = 'B';
	}
	for(int i=0; i<s.size(); i++){
		if(s[i] == '('){
			stk.push(i);
		}
		else if(s[i] == ')'){
			match[stk.top()] = i;
			stk.pop();
		}
	}
	if(s.empty()) return false;
	return f(0, s.size(), s);
}

int main(){
	int w;
	char str[MAXN];
	scanf("%d\n",&w);
	fgets(str, MAXN, stdin);
	string ret;
	for(int i=0; str[i]; i++){
		if(!isspace(str[i])) ret.push_back(str[i]);
	}
	if(!valid(ret)) puts("-1");
	else cout << count(ret.begin(), ret.end(), 'L') * w + count(ret.begin(), ret.end(), 'B') + 1 << endl;
}
