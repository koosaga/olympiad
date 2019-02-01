#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
#define sz(v) int((v).size())

const int MAXN = 10005;
const int MAXM = 12;

int n, m;
int num[MAXN][MAXM];
char buf[100];
map<string, int> mapper;

int main(){
	scanf("%d %d\n",&n,&m);
	for(int i=0; i<n; i++){
		fgets(buf, 100, stdin);
		vector<string> csv;
		string stk;
		for(int jj=0; buf[jj]; jj++){
			auto j = buf[jj];
			if(j == ',' || j == '\n'){
				csv.push_back(stk);
				stk.clear();
			}
			else stk.push_back(j);
		}
		if(stk.size()) csv.push_back(stk);
		assert(csv.size() == m);
		int cnt = 0;
		for(auto &j : csv){
			if(mapper.find(j) == mapper.end()){
				int sz = mapper.size();
				mapper[j] = sz;
			}
			num[i][cnt++] = mapper[j];
		}
	}
	for(int i=0; i<m; i++){
		for(int j=0; j<i; j++){
			vector<pi> v;
			for(int k=0; k<n; k++) v.emplace_back(num[k][i], num[k][j]);
			sort(v.begin(), v.end());
			for(int k=1; k<n; k++){
				if(v[k-1] == v[k]){
					puts("NO");
					vector<int> prnt;
					for(int l=0; l<n; l++){
						if(v[k] == pi(num[l][i], num[l][j])){
							prnt.push_back(l + 1);
							if(prnt.size() == 2) break;
						}
					}
					printf("%d %d\n", prnt[0], prnt[1]);
					printf("%d %d\n", j + 1, i + 1);
					exit(0);
				}
			}
		}
	}
	puts("YES");
}
