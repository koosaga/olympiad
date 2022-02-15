#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;
	enum type{
		EXPR,
		TERM,
		ATOM
	};
struct descent{
 
	type t;
	string s;
	char x;
	vector<descent*> child;
	descent(type _t){
		t = _t;
	}
	descent(string _s){
		t = TERM;
		s = _s;
	}
	descent(char _x){
		t = ATOM;
		x = _x;
	}
};
 
descent* parseExpr(string s);
 
descent* parseTerm(string s){
//	cout << "term(" << s << ")" << endl;
	{
		bool ok = 1;
		for(auto &x : s){
			if(x < 'A' || x > 'Z') ok = 0;
		}
		if(ok) return new descent(s);
	}
	vector<string> atoms;
	for(int i = 0; i < sz(s); i++){
		if(s[i] == '('){
			int j = i + 1, cnt = 1;
			while(j < sz(s) && cnt){
				if(s[j] == '(') cnt++;
				else if(s[j] == ')') cnt--;
				j++;
			}
			atoms.push_back(s.substr(i, j - i));
			i = j - 1;
		}
		else atoms.push_back(s.substr(i, 1));
	}
//	for(auto &i : atoms) cout << "atom(" << i << ")" << endl;
	auto isapp = [&](string s){
		return s == "+" || s == "*" || s == "?";
	};
	descent *ret = new descent(TERM);
	for(int i = sz(atoms) - 1; i >= 0; i--){
		int j = i;
		while(j >= 0 && isapp(atoms[j])) j--;
		if(j == i && i > 0 && atoms[j][0] != '(' && !isapp(atoms[j - 1]) && atoms[j - 1][0] != '('){
			atoms[j-1] += atoms[j];
			continue;
		}
		assert(j >= 0);
		if(atoms[j][0] == '(') atoms[j] = atoms[j].substr(1, sz(atoms[j]) - 2);
		descent *x = parseExpr(atoms[j]);
		for(int k = j + 1; k <= i; k++){
			descent *y = new descent(atoms[k][0]);
			y->child.push_back(x);
			x = y;
		}
		ret->child.push_back(x);
		i = j;
	}
	reverse(all(ret->child));
	return ret;
}
 
descent* parseExpr(string s){
//	cout << "expr(" << s << ")" << endl;
	vector<string> terms;
	string term;
	int cnt = 0;
	for(int i = 0; i < sz(s); i++){
		if(s[i] == '(') cnt++;
		else if(s[i] == ')') cnt--;
		else if(cnt == 0 && s[i] == '|'){
			terms.push_back(term);
			term.clear();
		}
		if(cnt > 0 || s[i] != '|') term.push_back(s[i]);
	}
	terms.push_back(term);
	if(sz(terms) == 1){
		return parseTerm(s);
	}
	descent *d = new descent(EXPR);
	for(auto &x : terms){
		d->child.push_back(parseTerm(x));
	}
	return d;
}
 
using output = vector<string>;
 
output printTree(descent *d){
	if(d->t == TERM){
		if(sz(d->child) == 0){
			int len = sz(d->s);
			output ret = {
				"+" + string(len + 2, '-') + "+",
				"+ " + d->s + " +",
				"+" + string(len + 2, '-') + "+"};
			return ret;
		}
		int width = 0;
		vector<output> rec;
		for(auto &x : d->child){
			rec.push_back(printTree(x));
			width = max(width, sz(rec.back()));
		}
		output op;
		for(int i = 0; i < width; i++){
			string s;
			for(int j = 0; j < sz(rec); j++){
				if(i != 1 && j > 0) s += "  ";
				if(i == 1 && j > 0) s += "->";
				if(sz(rec[j]) <= i) s += string(sz(rec[j][0]), ' ');
				else s += rec[j][i];
			}
			op.push_back(s);
		}
		return op;
	}
	if(d->t == ATOM){
		if(d->x == '+'){
			auto rec = printTree(d->child[0]);
			for(int i = 0; i < sz(rec); i++){
				if(i == 0) rec[i] = "   " + rec[i] + "   ";
				else if(i == 1) rec[i] = "+->" + rec[i] + "->+";
				else rec[i] = "|  " + rec[i] + "  |";
			}
			int width = sz(rec[0]);
			rec.push_back("|" + string(width - 2, ' ') + "|");
			rec.push_back("+<" + string(width - 3, '-') + "+");
			return rec;
		}
		if(d->x == '?'){
			auto rec = printTree(d->child[0]);
			for(int i = 0; i < sz(rec); i++){
				if(i >= 2) rec[i] = "   " + rec[i] + "   ";
				else if(i == 1) rec[i] = "+->" + rec[i] + "->+";
				else rec[i] = "|  " + rec[i] + "  |";
			}
			int width = sz(rec[0]);
			rec.insert(rec.begin(), "|" + string(width - 2, ' ') + "|");
			rec.insert(rec.begin(), "+" + string(width - 3, '-') + ">+");
			rec.insert(rec.begin(), string(width, ' '));
			return rec;
		}
		if(d->x == '*'){
			auto rec = printTree(d->child[0]);
			for(int i = 0; i < sz(rec); i++){
				if(i == 1) rec[i] = "+->" + rec[i] + "->+";
				else rec[i] = "|  " + rec[i] + "  |";
			}
			int width = sz(rec[0]);
			rec.insert(rec.begin(), "|" + string(width - 2, ' ') + "|");
			rec.insert(rec.begin(), "+" + string(width - 3, '-') + ">+");
			rec.insert(rec.begin(), string(width, ' '));
			rec.insert(rec.end(), "|" + string(width - 2, ' ') + "|");
			rec.insert(rec.end(), "+<" + string(width - 3, '-') + "+");
			return rec;
		}
	}
	if(d->t == EXPR){
		if(sz(d->child) == 1) return printTree(d->child[0]);
		vector<output> rec;
		int width = 0;
		for(auto &x : d->child){
			rec.push_back(printTree(x));
			width = max(width, sz(rec.back()[0]));
		}
		int st = 1e9, ed = -1e9;
 
		for(auto &i : rec){
			for(int j = 0; j < sz(i); j++){
				char chr;
				if(j == 1) chr = '-';
				else chr = ' ';
				while(sz(i[j]) < width) i[j].push_back(chr);
				if(j == 1){
					i[j] = "+->" + i[j] + "->+";
				}
				else{
					i[j] = "   " + i[j] + "   ";
				}
			}
		}
		width += 6;
		output op;
		for(int i = 0; i < sz(rec); i++){
			if(i) op.push_back(string(width, ' '));
			for(auto &j : rec[i]){
				if(j[0] == '+') st = min(st, sz(op)), ed = max(ed, sz(op));
				op.push_back(j);
			}
		}
		for(int i = st; i < ed; i++){
			if(op[i][0] != '+') op[i][0] = '|';
			if(op[i][sz(op[i]) - 1] != '+') op[i][sz(op[i]) - 1] = '|';
		}
		return op;
	}
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s; cin >> s;
	descent *x = parseExpr(s);
	auto y = printTree(x);
	for(int i = 0; i < sz(y); i++){
		if(i == 1) y[i] = "S->" + y[i] + "->F";
		else y[i] = "   " + y[i] + "   ";
	}
	cout << sz(y) << " " << sz(y[0]) << "\n";
	for(auto &i : y) cout << i << "\n";
}
 