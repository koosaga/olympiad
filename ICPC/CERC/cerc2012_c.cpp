#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

set<string> s;

int main(){
s.insert("h");
s.insert("he");
s.insert("li");
s.insert("be");
s.insert("b");
s.insert("c");
s.insert("n");
s.insert("o");
s.insert("f");
s.insert("ne");
s.insert("na");
s.insert("mg");
s.insert("al");
s.insert("si");
s.insert("p");
s.insert("s");
s.insert("cl");
s.insert("ar");
s.insert("k");
s.insert("ca");
s.insert("sc");
s.insert("ti");
s.insert("v");
s.insert("cr");
s.insert("mn");
s.insert("fe");
s.insert("co");
s.insert("ni");
s.insert("cu");
s.insert("zn");
s.insert("ga");
s.insert("ge");
s.insert("as");
s.insert("se");
s.insert("br");
s.insert("kr");
s.insert("rb");
s.insert("sr");
s.insert("y");
s.insert("zr");
s.insert("nb");
s.insert("mo");
s.insert("tc");
s.insert("ru");
s.insert("rh");
s.insert("pd");
s.insert("ag");
s.insert("cd");
s.insert("in");
s.insert("sn");
s.insert("sb");
s.insert("te");
s.insert("i");
s.insert("xe");
s.insert("cs");
s.insert("ba");
s.insert("hf");
s.insert("ta");
s.insert("w");
s.insert("re");
s.insert("os");
s.insert("ir");
s.insert("pt");
s.insert("au");
s.insert("hg");
s.insert("tl");
s.insert("pb");
s.insert("bi");
s.insert("po");
s.insert("at");
s.insert("rn");
s.insert("fr");
s.insert("ra");
s.insert("rf");
s.insert("db");
s.insert("sg");
s.insert("bh");
s.insert("hs");
s.insert("mt");
s.insert("ds");
s.insert("rg");
s.insert("cn");
s.insert("fl");
s.insert("lv");
s.insert("la");
s.insert("ce");
s.insert("pr");
s.insert("nd");
s.insert("pm");
s.insert("sm");
s.insert("eu");
s.insert("gd");
s.insert("tb");
s.insert("dy");
s.insert("ho");
s.insert("er");
s.insert("tm");
s.insert("yb");
s.insert("lu");
s.insert("ac");
s.insert("th");
s.insert("pa");
s.insert("u");
s.insert("np");
s.insert("pu");
s.insert("am");
s.insert("cm");
s.insert("bk");
s.insert("cf");
s.insert("es");
s.insert("fm");
s.insert("md");
s.insert("no");
s.insert("lr");

int t;
cin >> t;
while(t--){
	string str;
	bool dp[50005] = {}; dp[0] = 1;
	cin >> str;
	for(int i=1; i<=str.size(); i++){
		if(s.find(str.substr(i-1, 1)) != s.end()){
			dp[i] |= dp[i-1];
		}
		if(i >= 2 && s.find(str.substr(i-2, 2)) != s.end()){
			dp[i] |= dp[i-2];
		}
	}
	puts(dp[str.size()] ? "YES" : "NO");
}

}
