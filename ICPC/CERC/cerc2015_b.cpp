#include <bits/stdc++.h> 
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

char buf[500005];

int low[500005], len[500005], tot;
vector<int> v;

void preproc(){
	for(auto &i : v){
		for(int j=0; j<i; j++){
			len[tot+j] = i;
			low[tot+j] = tot;
		}
		len[tot+i] = -1;
		low[tot+i] = tot+i;
		tot += i + 1;
	}
	tot--;
}

int query(int x){
	int pos = 0;
	int iter = 0, ret = 0;
	while(pos < tot){
		iter++;
		ret += len[pos];
		pos = low[min(pos + x, tot)];
		if(len[pos] == -1){
			pos++;
		}
	}
	return ret + iter - 1;
}

int main(){
	fgets(buf, 500005, stdin);
	int cur = 0;
	for(int i=0; buf[i]; i++){
		if(buf[i] > 'z' || buf[i] < 'a'){
			if(cur) v.push_back(cur);
			cur = 0;
		}
		else cur++;
	}
	preproc();
	int s, e; cin >> s >> e;
	for(int i=s; i<=e; i++){
		printf("%d\n", query(i));
	}
}
