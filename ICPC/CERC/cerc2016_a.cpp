#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m;
char str[123][123];
bool sepl[123], sepr[123];

string norm(string s){
	string r = s;
	reverse(r.begin(), r.end());
	r = min(r, s);
	return r;
}

string solve(int sx, int ex, int sy, int ey){
	string s;
	for(int i=sx; i<=ex; i++){
		for(int j=sy; j<=ey; j++){
			s.push_back(str[i][j]);
		}
	}
	s = norm(s);
	if(ex - sx == ey - sy){
		string t;
		for(int i=sy; i<=ey; i++){
			for(int j=ex; j>=sx; j--){
				t.push_back(str[j][i]);
			}
		}
		s = min(s, norm(t));
	}
	return s;
}

int main(){
	cin >> n >> m;
	fill(sepl, sepl + n, 1);
	fill(sepr, sepr + m, 1);
	for(int i=0; i<n; i++) cin >> str[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] != '#') sepl[i] = sepr[j] = 0;
		}
	}
	vector<int> vl, vr;
	set<string> s;
	for(int i=0; i<n; i++) if(sepl[i]) vl.push_back(i);
	for(int i=0; i<m; i++) if(sepr[i]) vr.push_back(i);
	for(int i=0; i<vl.size()-1; i++){
		for(int j=0; j<vr.size()-1; j++){
			s.insert(solve(vl[i]+1, vl[i+1]-1, vr[j]+1, vr[j+1]-1));
		}
	}
	cout << s.size();
}
