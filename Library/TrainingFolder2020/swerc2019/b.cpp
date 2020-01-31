#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;

int n;
string s[MAXN];
char buf[69];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		s[i] = buf;
	}
	int piv = 0;
	int cnt = 1;
	for(int i=1; i<n; i++){
		if(s[piv] == s[i]) cnt++;
		else{
			cnt--;
			if(cnt == 0) piv = i + 1;
		}
	}
	string ans = "NONE";
	if(cnt != 0){
		cnt = count(s, s + n, s[piv]);
		if(cnt > n - cnt) ans = s[piv];
	}
	cout << ans << endl;
}
