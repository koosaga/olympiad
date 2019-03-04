#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const lint BIG = 1e18 + 1000000;

int n;
map<pair<int, vector<int>>, lint> mp;

bool good(vector<int> cnt){
	sort(cnt.begin(), cnt.end());
	for(int i=0; i<26-n; i++){
		if(cnt[i] > 0) return 0;
	}
	for(int i=0; i<n; i++){
		if(cnt[26-n+i] > i + 1 ) return 0;
	}
	return 1;
}


lint bktk(int prv, vector<int> cnt){
	if(accumulate(cnt.begin(), cnt.end(), 0) == n * (n + 1) / 2) return 1;
	int cprv = cnt[prv];
	sort(cnt.begin(), cnt.end());
	for(int i=0; i<26; i++){
		if(cnt[i] == cprv){
			prv = i;
			break;
		}
	}
	if(mp.find(make_pair(prv, cnt)) != mp.end()) return mp[make_pair(prv, cnt)];
	lint ret = 0;
	for(int i=0; i<26; i++){
		if(i != prv){
			cnt[i]++;
			if(!good(cnt)){
				cnt[i]--;
				continue;
			}
			ret += bktk(i, cnt);
			cnt[i]--;
			if(ret > BIG) break;
		}
	}
	ret = min(ret, BIG + 1);
	return mp[make_pair(prv, cnt)] = ret;
}

void gen(int prv, vector<int> cnt, string s, lint k){
	if(s.size() == n * (n + 1) / 2){
		cout << s << endl;
		return;
	}
	for(int i=0; i<26; i++){
		if(prv != i){
			cnt[i]++;
			if(!good(cnt)){
				cnt[i]--;
				continue;
			}
			lint getv = bktk(i, cnt);
			if(getv >= k){
				s.push_back(i + 'a');
				gen(i, cnt, s, k);
				return;
			}
			k -= getv;
			cnt[i]--;
		}
	}
	puts("-1");
	exit(0);
}

int main(){
	lint m;
	cin >> n >> m;
	vector<int> v(26);
	string s;
	if(n <= 16){
		gen(-1, v, s, m);
	}
	else{
		for(int i=0; i<n-1; i++) s = s + "ab";
		s = s + "a";
		for(int i=0; i<n-3; i++) s = s + "cd";
		s = s + "c";
		for(int i=0; i<n-5; i++) s = s + "ef";
		s = s + "e";
		for(auto &i : s) v[i - 'a']++;
		gen(4, v, s, m);
	}
}
