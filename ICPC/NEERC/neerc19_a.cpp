#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <memory.h> 
#include <math.h> 
#include <assert.h> 
#include <stack> 
#include <queue> 
#include <map> 
#include <set> 
#include <string> 
#include <algorithm> 
#include <iostream> 
#include <functional>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
typedef pair<lint, lint> pi;
const int MAXN = 200005;
const int mod = 1e9 + 7; 

struct work{
	lint s, e, x;
	bool operator<(const work &w)const{
		return s < w.s;
	}
}a[MAXN];
int n;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%lld %lld %lld",&a[i].s,&a[i].e,&a[i].x);
	}
	set<pi> not_on;
	set<pi> now_on;
	sort(a, a + n);
	for(int i=0; i<n; i++) not_on.emplace(a[i].s + a[i].x, i);
	lint last_work = -1;
	int ptr = 0;
	lint ret = 0;
	while(true){
		while(ptr < n && a[ptr].s <= last_work){
			int i = ptr;
			not_on.erase(pi(a[i].s + a[i].x, i));
			now_on.emplace(a[i].x, i);
			ptr++;
		}
		vector<pi> candidates;
		auto it1 = not_on.begin();
		auto it2 = now_on.begin();
		for(int i=0; i<1; i++){
			if(it1 != not_on.end()){
				candidates.push_back(*it1);
				it1++;
			}
			while(it2 != now_on.end() && last_work + it2->first > a[it2->second].e){
				it2 = now_on.erase(it2);
			}
			if(it2 != now_on.end()){
				candidates.emplace_back(last_work + it2->first, it2->second);
				it2++;
			}
		}
		sort(all(candidates));
		if(sz(candidates) == 0) break;
		int i = candidates[0].second;
		last_work = max(last_work, a[i].s);
		lint howmuch = a[i].e;
		if(ptr < n) howmuch = min(howmuch, a[ptr].s);
		howmuch = max((howmuch - last_work) / a[i].x, 1ll);
		last_work += howmuch * a[i].x;
		ret += howmuch;
	}
	cout << ret << endl;
}
