#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

vector<string> vect;
string s;
short lcp[MAXN][MAXN];
short lcp2[MAXN][MAXN];
short len[MAXN][MAXN];
short good[MAXN][MAXN];
int sfx[MAXN];

int trie[MAXN][26], piv, term[MAXN];

void precalc_good(){
	for(auto &i : vect){
		int p = 0;
		for(auto &j : i){
			if(!trie[p][j - 'A']){
				trie[p][j - 'A'] = ++piv;
			}
			p = trie[p][j - 'A'];
		}
		term[p] = 1;
	}
	for(int i=0; i<s.size(); i++){
		int p = 0, failed = 0;
		for(int j=i; j<s.size(); j++){
			if(!trie[p][s[j] - 'A']){
				failed = 1;
			}
			if(failed){
				good[i][j + 1] = 1;
				continue;
			}
			p = trie[p][s[j] - 'A'];
			good[i][j + 1] = !term[p];
			if(!good[i][j + 1]) continue;
		}
	}

}

void do_dynamic(){
	int cur = 0, ps = -1, pe = -1;
	for(int i=1; i<=s.size(); i++){
		for(int j=0; j<s.size(); j++){
			if(sfx[j] + i > s.size()) continue;
			if(!good[sfx[j]][sfx[j] + i]) continue;
			int e = j;
			while(e < s.size() && lcp[sfx[j]][sfx[e]] >= i) e++;
			bool good2 = 1;
			for(int k=j+1; k<e; k++){
				if(lcp2[sfx[j]][sfx[k]] < i) good2 = 0;
			}
			if(!good2){
				j = e - 1;
				continue;
			}
			vector<int> vect(sfx + j, sfx + e);
			sort(vect.begin(), vect.end());
			int prev = -1e9, occurence = 0;
			for(auto &j : vect){
				if(prev + i <= j){
					prev = j;
					occurence++;
				}
			}
			int saved = (occurence - 1) * (len[sfx[j]][sfx[j] + i] - i) - i;
			if(saved > cur){
				cur = saved;
				ps = i;
				pe = sfx[j];
			}
			j = e - 1;
		}
	}
	if(cur == 0){
		puts("0");
	}
	else{
		cout << cur << endl;
		cout << s.substr(pe, ps) << endl;
	}
}

int main(){
	string stk;
	{
		while(true){
			char c = getchar();
			if(c <= 0) break;
			if(islower(c)) c += 'A' - 'a';
			if(isupper(c)){
				stk.push_back(c);
			}
			else{
				if(stk.size()) vect.push_back(stk);
				stk.clear();
			}
		}
		if(stk.size()) vect.push_back(stk);
	}
	for(auto &i : vect) s += i[0];
	for(int i=s.size()-1; i>=0; i--){
		for(int j=s.size()-1; j>=0; j--){
			if(s[i] == s[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;
			if(vect[i] == vect[j]) lcp2[i][j] = lcp2[i + 1][j + 1] + 1;
		}
	}
	for(int i=0; i<s.size(); i++){
		for(int j=i; j<s.size(); j++){
			len[i][j + 1] = len[i][j] + vect[j].size();
		}
	}
	iota(sfx, sfx + s.size(), 0);
	sort(sfx, sfx + s.size(), [&](const int &a, const int &b){
		return s.substr(a, s.size() - a) < s.substr(b, s.size() - b);
	});
	precalc_good();
	do_dynamic();
}
