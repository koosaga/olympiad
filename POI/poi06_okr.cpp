#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;
 
const int mod1 = 1e9 + 513;
const int mod2 = 1e9 + 531;
 
int n;
char str[1000005];
 
lint hash1[1000005], hash2[1000005];
lint pow1[1000005], pow2[1000005];
 
void prep_hash(){
	pow1[0] = pow2[0] = 1;
	for (int i=1; i<n; i++) {
		pow1[i] = pow1[i-1] * 26 % mod1;
		pow2[i] = pow2[i-1] * 26 % mod2;
	}
	for (int i=0; i<n; i++) {
		hash1[i] += str[i] - 'a';
		hash2[i] += str[i] - 'a';
		if(i) hash1[i] += hash1[i-1] * 26;
		if(i) hash2[i] += hash2[i-1] * 26;
		hash1[i] %= mod1;
		hash2[i] %= mod2;
	}
}
 
bool hash_match(int s1, int e1, int s2, int e2){
	if(s1 > e1) return 1;
	int l = e1 - s1 + 1;
	lint h11 = hash1[e1] - (s1 ? hash1[s1-1] * pow1[l] : 0) % mod1 + mod1;
	lint h12 = hash2[e1] - (s1 ? hash2[s1-1] * pow2[l] : 0) % mod2 + mod2;
	lint h21 = hash1[e2] - (s2 ? hash1[s2-1] * pow1[l] : 0) % mod1 + mod1;
	lint h22 = hash2[e2] - (s2 ? hash2[s2-1] * pow2[l] : 0) % mod2 + mod2;
	h11 %= mod1;
	h12 %= mod2;
	h21 %= mod1;
	h22 %= mod2;
	return (h11 == h21 && h12 == h22);
}
 
bool qadd[1000005];
vector<int> qdel[1000005];
multiset<int> s;
 
int main(){
	scanf("%d %s",&n,str);
	prep_hash();
	for (int i=1; i<=n; i++) {
		int s = 0, e = min(i,n-i);
		while (s != e) {
			int m = (s+e+1)/2;
			if(hash_match(0,m-1,i,i+m-1)) s = m;
			else e = m-1;
		}
		if(s == 0) continue;
		qadd[i] = 1;
		qdel[i+s-1].push_back(i);
	}
	lint ret = 0;
	for (int i=0; i<n; i++) {
		if(qadd[i]) s.insert(i);
		if(!s.empty()) ret += *s.rbegin();
		for (auto &j : qdel[i]){
			s.erase(s.find(j));
		}
	}
	printf("%lld",ret);
}