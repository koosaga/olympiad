#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 2005;

#define FUCK if(wrong) return pi(-1, -1)
char sym[9] = "01+-*()=";

string s;

pi pE(int st, int ed);
pi pT(int st, int ed);
pi pF(int st, int ed);
pi pN(int st, int ed);

bool wrong;

void ass(bool p){
	if(!p) wrong = 1;
}

pi pN(int st, int ed){
	FUCK;
//	printf("Calling pN(%d, %d)\n", st, ed);
	string t;
	FUCK;
	while(ed > st && isdigit(s[ed-1])){
		FUCK;
		t.push_back(s[--ed]);
		FUCK;
	}
	FUCK;
	reverse(t.begin(), t.end());
	FUCK;
	ass(!t.empty());
	FUCK;
	if(t.size() == 1) return pi(t[0] - '0', ed);
	else{
		FUCK;
		ass(t[0] == '1');
		FUCK;
		int ans = 0;
		for(auto &j : t) ans = (ans * 2) + (j - '0');
		return pi(ans, ed);
	}
}

pi pF(int st, int ed){
	FUCK;
//	printf("Calling pF(%d, %d)\n", st, ed);
	if(s[ed-1] == ')'){
		FUCK;
		int cnt = 1, pnt = -1;
		for(int j=ed-2; j>=0; j--){
			if(s[j] == ')') cnt++;
			else if(s[j] == '(') cnt--;
			if(cnt == 0){
				pnt = j;
				break;
			}
		}
		FUCK;
		ass(pnt != -1);
		FUCK;
		auto x = pE(pnt + 1, ed-1);
		FUCK;
		ass(x.second == pnt + 1);
		FUCK;
		x.second = pnt;
		FUCK;
		return x;
	}
	else{
		FUCK;
		ass(isdigit(s[ed-1]));
		FUCK;
		auto x = pN(st, ed);
		FUCK;
		return x;
	}
}

pi pT(int st, int ed){
	FUCK;
//	printf("Calling pT(%d, %d)\n", st, ed);
	pi nxt = pF(st, ed);
	FUCK;
	if(nxt.second == st) return nxt;
	if(s[nxt.second - 1] == '-'){
		for(int j=nxt.second - 1; j>=st; j--){
			if(s[j] == '*'){
				int cnt = (nxt.second - j - 1) % 2;
				auto x = pT(st, j);
				FUCK;
				return pi(x.first * nxt.first * (cnt ? -1 : 1), x.second);
			}
			if(s[j] != '-') break;
		}
	}
	if(s[nxt.second - 1] != '*') return nxt;
	FUCK;
	auto x = pT(st, nxt.second - 1);
	FUCK;
	return pi(x.first * nxt.first, x.second);
}

pi pE(int st, int ed){
	FUCK;
//	printf("Calling pE(%d, %d)\n", st, ed);
	pi nxt = pT(st, ed);
	FUCK;
	if(nxt.second == st) return nxt;
	else if(s[nxt.second - 1] == '+'){
		FUCK;
		auto x = pE(st, nxt.second - 1);
		FUCK;
		return pi(x.first + nxt.first, x.second);
	}
	else if(s[nxt.second - 1] == '-'){
		int flg = 1;
		while(nxt.second > st && s[nxt.second - 1] == '-') nxt.second--, flg = -flg;
		FUCK;
		if(nxt.second == st) return pi(flg * nxt.first, nxt.second);
		else if(s[nxt.second - 1] == '+'){
			FUCK;
			auto x = pE(st, nxt.second - 1);
			FUCK;
			return pi(x.first + flg * nxt.first, x.second);
		}
		else{

			auto x = pE(st, nxt.second);
			FUCK;
			return pi(x.first + flg * nxt.first, x.second);
		}
	}
	else return nxt;
}

int eval(string S){
//	fprintf(stderr, "trying %s\n", S.c_str());
	if(S.empty()){
		wrong = 1; 
		return -1;
	}
	s = S;
	auto x = pE(0, s.size());
	if(x.second != 0) wrong = 1;
	return x.first;
}

bool solve(string s){
	if(count(s.begin(), s.end(), '=') != 1) return 0;
	for(int i=0; i<s.size(); i++){
		if(s[i] == '='){
			wrong = 0;
			int x = eval(s.substr(0, i));
			int y = eval(s.substr(i+1, s.size() - i - 1));
			if(x == y && !wrong) return 1;
			return 0;
		}
	}
	return 0;
}

int main(){
	string s;
	cin >> s;/*
	wrong = 0;
	cout << eval("0") << endl;
	wrong = 0;
	cout << eval("-(0)") << endl;
	wrong = 0;
	cout << eval("(-0)") << endl;
	wrong = 0;
	cout << eval("-0") << endl;
	wrong = 0;
	cout << eval("(0)") << endl;
	wrong = 0;
	*/
	set<char> st;
	for(auto &i : s) if(isalpha(i)) st.insert(i);
	sort(sym, sym + 8);
	if(st.size() > 8){
		cout << 0 << endl;
		return 0;
	}
	int prd = 1, itr = 0, ans = 0;
	for(int i=1; i<=8-st.size(); i++) prd *= i;
	do{
		if(itr % prd){
			itr++;
			continue;
		}
		itr++;
		int cnt = 0;
		string t = s;
		for(auto &i : st){
			for(auto &j : t){
				if(i == j) j = sym[cnt];
			}
			cnt++;
		}
		if(solve(t)){
		//	cout << t << endl;
			ans++;
		}
	}while(next_permutation(sym, sym + 8));
	cout << ans << endl;
}
