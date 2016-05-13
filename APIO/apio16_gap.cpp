#include "gap.h"
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

pi query(lint s, lint e){
	pi ret;
	MinMax(s, e, &ret.first, &ret.second);
	return ret;
}

long long findGap(int T, int N)
{
	vector<lint> a;
	lint ret = 0;
	if(T == 1){
		lint s = 0, e = 2e18;
		while(N >= 1){
			auto t = query(s, e);
			a.push_back(t.first);
			a.push_back(t.second);
			s = t.first + 1, e = t.second - 1;
			N -= 2;
		}
	}
	else{
		pi q = query(0, 2e18);
		lint triv = (q.second - q.first + N - 2) / (N - 1);
		ret = triv;
		for(lint p = q.first; p <= q.second; p += triv + 1){
			auto t = query(p, p + triv);
			a.push_back(t.first);
			a.push_back(t.second);
		}
	}
	sort(a.begin(), a.end());
	for(int i=0; i<a.size()-1; i++){
		ret = max(ret, a[i+1] - a[i]);
	}
	return ret;
}
