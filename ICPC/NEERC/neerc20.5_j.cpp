#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
using lint = long long;

char str[MAXN];

int main(){
	scanf("%s", str);
	int n = strlen(str);
	if(str[0] == '#' || str[n-1] == '#'){
		if(str[0] != '#' || str[n-1] != '#'){
			puts("-1");
			return 0;
		}
		int cur = 1;
		vector<int> v;
		for(int i = 1; i < n; i++){
			if(str[i-1] == '_' && str[i] == '_'){
				puts("-1");
				return 0;
			}
			if(str[i] == '#') cur++;
			else{
				v.push_back(cur); cur = 0;
			}
		}
		v.push_back(cur); cur = 0;
		printf("%d\n", sz(v));
		for(auto &i : v) printf("%d ", i);
		return 0;
	}
	vector<int> v;
	vector<pi> info;
	{
		int cur = 0;
		for(int i = 0; i < n; i++){
			if(str[i] == '_') cur++;
			else{
				if(cur){
					v.push_back(cur);
					info.emplace_back(i - cur, i - 1);
				}
				cur = 0;
			}
		}
		if(cur){
			v.push_back(cur);
			info.emplace_back(n - cur, n - 1);
		}
		if(sz(v) == 1){
			puts("0");
			return 0;
		}
	}
	int B = sz(v) - 1;
	int sumA = count(str, str + n, '#');
	for(int G = 1; ; G++){
		lint low = sumA + B * G + B;
		if(low > n) break;
		bool fuck = 0;
		for(int j = 0; j < sz(v); j++){
			int func = v[j] - G;
			if(j < sz(v) - 1 && j > 0) func--;
			if(func < 0) fuck = 1;
			if(func == 1) fuck = 1;
			if(func % 2 && G == 1) fuck = 1;
			low += func;
		}
		if(!fuck && low == n + 1 - G){
			vector<int> ans;
			for(int j = 0; j < sz(v); j++){
				if(j > 0){
					int saiBlock = info[j].first - info[j-1].second - 1;
					ans.push_back(saiBlock + G);
				}
				int func = v[j] - G;
				if(j < sz(v) - 1 && j > 0) func--;
				for(int j = 0; j < func / 2; j++){
					ans.push_back(1);
				}
				if(func % 2) ans.back()++;
			}
			printf("%d\n", sz(ans));
			for(auto &i : ans) printf("%d ", i);
			return 0;
		}
	}
	puts("-1");
}
