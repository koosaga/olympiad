#include <bits/stdc++.h>
using namespace std; 
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 105;

int n, m, a[MAXN][MAXN];
int chk[MAXN][MAXN], col[MAXN], imp;

void dfs(int x, int c){
	if(col[x]){
		if(col[x] != c) imp = 1;
		return;
	}
	col[x] = c;
	for(int i=0; i<100; i++){
		if(chk[x][i] != -1){
			dfs(i, (chk[x][i] ? (3 - c) : c));
		}
	}
}

int inverse(vector<int> &v){
	int ans = 0;
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<i; j++){
			if(v[j] > v[i]) ans++;
		}
	}
	return ans & 1;
}

vector<string> ans;

void Do(char t, int x){
	if(t == 'R'){
		reverse(a[x], a[x] + m);
	}
	else{
		for(int i=0; i<n-i-1; i++){
			swap(a[i][x], a[n-i-1][x]);
		}
	}
	char buf[10];
	sprintf(buf, "%c%d", t, x+1);
	ans.push_back(string(buf));
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		ans.clear();
		imp = 0;
		memset(chk, -1, sizeof(chk));
		memset(col, 0, sizeof(col));
		scanf("%d %d",&n,&m);
		swap(n, m);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				scanf("%d",&a[i][j]);
			}
		}
		if(m % 2 == 1){
			vector<int> v;
			for(int i=0; i<n; i++){
				v.push_back(a[i][m/2]);
			}
			if(!is_sorted(v.begin(), v.end()) && !is_sorted(v.rbegin(), v.rend())){
				puts("IMPOSSIBLE");
				continue;
			}
			if(is_sorted(v.rbegin(), v.rend())){
				Do('C', m/2);
			}
		}
		if(n % 2 == 1){
			vector<int> v(a[n/2], a[n/2] + m);
			if(!is_sorted(v.begin(), v.end()) && !is_sorted(v.rbegin(), v.rend())){
				puts("IMPOSSIBLE");
				continue;
			}
			if(is_sorted(v.rbegin(), v.rend())){
				Do('R', n/2);
			}
		}
		for(int i=0; i<n/2; i++){
			for(int j=0; j<m/2; j++){
				vector<int> v = {a[i][j], a[i][m-1-j], a[n-i-1][j], a[n-i-1][m-j-1]};
				chk[i][j + n / 2] = chk[j + n / 2][i] = inverse(v) % 2;
			}
		}
		for(int i=0; i<n/2+m/2; i++){
			if(!col[i]){
				dfs(i, 1);
			}
		}
		if(imp){
			puts("IMPOSSIBLE");
			continue;
		}
		for(int i=0; i<n/2; i++){
			if(col[i] == 2){
				Do('R', i);
			}
		}
		for(int i=0; i<m/2; i++){
			if(col[i + n/2] == 2){
				Do('C', i);
			}
		}
		for(int i=0; i<n/2; i++){
			for(int j=0; j<m/2; j++){
				vector<int> v = {a[i][j], a[i][m-1-j], a[n-i-1][j], a[n-i-1][m-j-1]};
				int p = min_element(v.begin(), v.end()) - v.begin();
				if(p == 3){
					Do('C', m-1-j);
					Do('R', i);
					Do('C', m-1-j);
					Do('R', i);
					p = 1;
				}
				if(p == 1){
					Do('R', i);
					Do('C', j);
					Do('R', i);
					Do('C', j);
				}
				if(p == 2){
					Do('C', j);
					Do('R', i);
					Do('C', j);
					Do('R', i);
				}
			}
		}
		for(int i=0; i<n/2; i++){
			for(int j=0; j<m/2; j++){
				vector<int> v = {a[i][j], a[i][m-1-j], a[n-i-1][j], a[n-i-1][m-j-1]};
				assert(min_element(v.begin(), v.end()) == v.begin());
				int p = max_element(v.begin(), v.end()) - v.begin();
				if(p == 1){
					Do('C', m-1-j);
					Do('R', n-1-i);
					Do('C', m-1-j);
					Do('R', n-1-i);
				}
				if(p == 2){
					Do('R', n-1-i);
					Do('C', m-1-j);
					Do('R', n-1-i);
					Do('C', m-1-j);
				}
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(a[i][j] != i * m + j + 1){
					imp = 1;
				}
			}
		}
		if(imp){
			puts("IMPOSSIBLE");
			continue;
		}
		printf("POSSIBLE %d ", ans.size());
		for(auto &i : ans) printf("%s ", i.c_str());
		puts("");
	}
}
