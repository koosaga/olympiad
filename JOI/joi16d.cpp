#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<lint, lint>;

int n, k;
char str[MAXN];

vector<pi> canon(vector<pi> v){
	vector<pi> ev;
	for(auto &i : v){
		ev.emplace_back(i.first, +1);
		ev.emplace_back(i.second + 1, -1);
	}
	sort(ev.begin(), ev.end());
	vector<pi> ret;
	int cnt = 0;
	for(int i=0; i+1<ev.size(); i++){
		cnt += ev[i].second;
		if(ev[i].first != ev[i + 1].first){
			if(cnt > 0){
				ret.emplace_back(ev[i].first, ev[i + 1].first);
			}
		}
	}
	return ret;
}

lint getInsecLength(vector<pi> a, vector<pi> b, vector<pi> c, vector<pi> d){
	vector<pi> ev;
	for(auto &i : a){
		ev.emplace_back(i.first, +1);
		ev.emplace_back(i.second, -1);
	}
	for(auto &i : b){
		ev.emplace_back(i.first, +1);
		ev.emplace_back(i.second, -1);
	}
	for(auto &i : c){
		ev.emplace_back(i.first, +1);
		ev.emplace_back(i.second, -1);
	}
	for(auto &i : d){
		ev.emplace_back(i.first, +1);
		ev.emplace_back(i.second, -1);
	}
	sort(ev.begin(), ev.end());
	int cnt = 0; lint ret = 0;
	for(int i=0; i+1<ev.size(); i++){
		cnt += ev[i].second;
		if(ev[i].first != ev[i + 1].first){
			if(cnt == 4){
				ret += ev[i + 1].first - ev[i].first;
			}
		}
	}
	return ret;

}

int main(){
	scanf("%d %d",&n,&k);
	scanf("%s", str);
	vector<pi> v = {pi(0, 0)};
	lint px = 0, py = 0;
	for(int j=0; j<n; j++){
		if(str[j] == 'E') px++;
		if(str[j] == 'W') px--;
		if(str[j] == 'N') py++;
		if(str[j] == 'S') py--;
		v.emplace_back(px, py);
	}
	if(v.back().first < 0){
		for(auto &i : v) i.first *= -1;
	}
	if(v.back().second < 0){
		for(auto &i : v) i.second *= -1;
	}
	if(v.back().first == 0){
		for(auto &i : v) swap(i.first, i.second);
	}
	pi vect;
	if(v.back() == pi(0, 0)){
		k = 1;
		vect = pi(1e6, 1e6);
	}
	else{
		vect = v.back();
	}
	v.pop_back();
	map<pi, vector<pi>> mp;
	for(int i=0; i<v.size(); i++){
		lint px = v[i].first;
		lint py = v[i].second;
		lint s = 0, e = k - 1;
		if(i == 0) e = k;
		if(px >= vect.first){
			lint delta = px / vect.first;
			px -= delta * vect.first;
			py -= delta * vect.second;
			s += delta;
			e += delta;
		}
		if(px < 0){
			lint delta = (vect.first - px - 1) / vect.first;
			px += delta * vect.first;
			py += delta * vect.second;
			s -= delta;
			e -= delta;
		}
		assert(px >= 0 && px < vect.first);
	//	printf("event %lld %lld = [%lld, %lld]\n", px, py, s, e);
		mp[pi(px, py)].emplace_back(s, e);
	}
	for(auto &i : mp){
		i.second = canon(i.second);
	}
	lint ret = 0;
	for(auto &i : mp){
		lint x, y; tie(x, y) = i.first;
		auto n2 = pi(x, y + 1);
		auto n3 = pi(x + 1, y);
		auto n4 = pi(x + 1, y + 1);
		if(x + 1 == vect.first){
			n3.first -= vect.first;
			n3.second -= vect.second;
			n4.first -= vect.first;
			n4.second -= vect.second;
		}
		if(mp.count(n2) && mp.count(n3) && mp.count(n4)){
			auto i1 = i.second;
			auto i2 = mp[n2];
			auto i3 = mp[n3];
			auto i4 = mp[n4];
			if(x + 1 == vect.first){
				for(auto &x : i3){
					x.first--; x.second--;
				}
				for(auto &x : i4){
					x.first--; x.second--;
				}
			}
			ret += getInsecLength(i1, i2, i3, i4);
		}
	}
	cout << ret << endl;
	return 0;
}
