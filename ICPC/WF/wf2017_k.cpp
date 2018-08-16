#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 15;

int n, m, ans[MAXN];
string s[MAXN];
vector<int> fseq[MAXN];
char buf[100005];
int fail[100005];

int main(){
	scanf("%d %d",&m,&n);
	fail[0] = -1;
	for(int i=0; i<n; i++){
		ans[i] = i;
		scanf("%s", buf); s[i] = buf;
		int p = 0;
		for(int j=1; buf[j]; j++){
			while(p && buf[j] != buf[p]) p = fail[p];
			if(buf[j] == buf[p]) p++;
			fail[j + 1] = p;
		}
		int pos = s[i].size();
		while(pos >= 0 && pos >= 2 * (int)s[i].size() - m){
			fseq[i].push_back(pos);
			pos = fail[pos];
		}
	}
	sort(ans, ans + n, [&](const int &a, const int &b){
		return make_pair(fseq[a], a) < make_pair(fseq[b], b);
	});
	for(int i=0; i<n; i++) puts(s[ans[i]].c_str());
}

