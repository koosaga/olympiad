#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

int n, c;
pi a[MAXN];

struct foo{
	int chances;
	int delta;
	int idx;
	bool flag;
	bool operator<(const foo &f)const{
        if(delta == f.delta) return flag > f.flag;
		return delta < f.delta;
	}
};

vector<foo> v;

bool trial(lint T){
	vector<lint> howAdd(n);
	lint Q = min((__int128)1e15, (__int128) c * T);
	vector<int> eventFin, eventPut; 
	vector<pi> eventPutTmp;
	for(auto &x : v){
		if(x.flag == 0){
			lint canTry = min({Q, T - howAdd[x.idx], 1ll * x.chances});
			Q -= canTry;
			howAdd[x.idx] += canTry;
			eventPutTmp.emplace_back(x.idx, min((lint)1e9, canTry));
		}
		else{
			lint canTry = min({T - howAdd[x.idx], 1ll * x.chances});
			if(canTry > 0){
				eventFin.push_back(x.idx);
			}
		}
	}
	if(Q > 0) eventPutTmp.emplace_back(-1, (int)min((lint)1e9, Q));
	reverse(all(eventPutTmp));
	for(auto &[idx, cnt] : eventPutTmp){
		while(cnt > 0 && sz(eventPut) < sz(eventFin)){
			cnt--;
			eventPut.push_back(idx);
		}
	}
	lint sum = 0;
	auto manip = [&](int pos, int delta){
		if(pos == -1) return;
		lint cur = a[pos].first - howAdd[pos] * a[pos].second;
		if(cur <= 0) return;
		cur = max(cur - a[pos].second, 0ll)  + 1;
		sum += delta * cur;
	};
	for(int i = 0; i < n; i++){
		manip(i, +1);
	}
	if(sum <= c) return true;
	lint cnt = accumulate(all(howAdd), 0ll);
	for(int i = 0; i < sz(eventFin); i++){
		manip(eventFin[i], -1);
		if(i < sz(eventPut)) manip(eventPut[i], -1);
		howAdd[eventFin[i]]++;
		cnt++;
		if(i < sz(eventPut) && eventPut[i] != -1) howAdd[eventPut[i]]--, cnt--;
		manip(eventFin[i], +1);
		if(i < sz(eventPut)) manip(eventPut[i], +1);
		if(sum <= c && cnt <= (__int128) c * T) return true;
	}
	return false;
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> c;
	for(int i = 0; i < n; i++){
		cin >> a[i].first >> a[i].second;
		int D = (a[i].first - 1) / a[i].second;
		if(D > 0) v.push_back({D, a[i].second, i, 0});
		int d = a[i].first - D * a[i].second;
		v.push_back({1, d, i, 1});
	}
	sort(all(v));
	reverse(all(v));
	lint s = 0, e = 1e15;
	while(s != e){
		lint m = (s + e) / 2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	cout << s << endl;
}

