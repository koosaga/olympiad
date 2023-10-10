#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int a[14];
int cnt[10];
bool vis[14];

bool bktk(int x){
	if(x == 4){
		int ans = 0;
		for(int i=0; i<14; i++){
			if(!vis[i]) ans ^= a[i];
		}
		return ans == 0;
	}
	for(int i=0; i<14; i++){
		if(vis[i]) continue;
		for(int j=0; j<i; j++){
			if(vis[j]) continue;
			for(int k=0; k<j; k++){
				if(vis[k]) continue;
				vis[i] = vis[j] = vis[k] = 1;
				if(((a[i] == a[j] && a[j] == a[k]) ||
						(a[i] - 1 == a[j] && a[j] - 1 == a[k])) && bktk(x+1)){
					return 1;
				}
				vis[i] = vis[j] = vis[k] = 0;
			}
		}
	}
	return 0;
}

bool solve(){
	memset(vis, 0, sizeof(vis));
	int aux[14] = {};
	memcpy(aux, a, sizeof(aux));
	sort(a, a+14);
	bool ret = 1;
	for(int i=0; i<14; i+=2){
		if(a[i] != a[i+1]){
			ret = 0;
			break;
		}
	}
	for(int i=1; i<13; i+=2){
		if(a[i] == a[i+1]){
			ret = 0;
			break;
		}
	}
	if(!ret) ret |= bktk(0);
	memcpy(a, aux, sizeof(a));
	return ret;
}

int main(){
	for(int i=0; i<13; i++){
		cin >> a[i];
		cnt[a[i]]++;
	}
	vector<int> v;
	for(int i=1; i<=9; i++){
		if(cnt[i] != 4){
			a[13] = i;
			if(solve()) v.push_back(i);
		}
	}
	if(v.empty()) puts("-1");
	for(auto &i : v) printf("%d ", i);
}
