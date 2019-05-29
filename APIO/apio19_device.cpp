#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int MAXT = 4200000;
using lint = long long;
using pi = pair<lint, lint>;

lint gcd(lint x, lint y){
	return y ? gcd(y, x%y) : x;
}

struct event{
	lint pos, st, ed;
	int dx;
	bool operator<(const event &e)const{
		return pos != e.pos ? pos < e.pos : dx > e.dx;
	}
};

struct strip{
	lint fuck, pos, dx;
	bool operator<(const strip &s)const{
		return pi(fuck, pos) < pi(s.fuck, s.pos);
	}
};

int n;
lint a, b, l[MAXN], r[MAXN];
map<lint, int> mp;
vector<strip> strips;

int main(){
	scanf("%d",&n);
	scanf("%lld %lld",&a,&b);
	for(int i=0; i<n; i++){
		scanf("%lld %lld",&l[i],&r[i]);
	}
	lint period = a / gcd(a, b + 1);
	for(int i=0; i<n; i++){
		vector<lint> v = {l[i] % b, 0, (r[i] + 1) % b};
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		int ptr = 0;
		vector<event> tev;
		map<lint, int> dx;
		int cnt = 0;
		for(auto &j : v){
			ptr++;
			lint s = l[i] + b - j;
			lint e = r[i] + b - j;
			s = (s + b - 1) / b;
			e /= b;
			lint is = j;
			lint ie = (ptr < v.size() ? v[ptr] : b);
			if(e - s + 1 >= period){
				tev.push_back({is, 0, period, +1});
				tev.push_back({ie, 0, period, -1});
				dx[0]++;
				dx[period]--;
			}
			else if(s <= e){
				if(s % period > e % period){
					tev.push_back({is, s % period, period, +1});
					tev.push_back({ie, s % period, period, -1});
					tev.push_back({is, 0, e % period + 1, +1});
					tev.push_back({ie, 0, e % period + 1, -1});
					dx[s % period]++;
					dx[period]--;
					dx[0]++;
					dx[e % period + 1]--;
				}
				else{
					tev.push_back({is, s % period, e % period + 1, +1});
					tev.push_back({ie, s % period, e % period + 1, -1});
					dx[s % period]++;
					dx[e % period + 1]--;
				}
			}
			cnt++;
		}
		auto nitr = dx.begin();
		int tcnt = 0;
		for(auto &i : dx){
			nitr++;
			tcnt += i.second;
			if(nitr == dx.end()) break;
			if(tcnt == cnt){
				mp[i.first]++;
				mp[nitr->first]--;
			}
			else{
				for(auto &j : tev){
					lint st = max(i.first, j.st);
					lint ed = min(nitr->first, j.ed);
					for(lint jj = st; jj < ed; jj++){
						strips.push_back({jj, j.pos, j.dx});
					}
				}
			}
		}
	}
	auto nitr = mp.begin();
	int tcnt = 0;
	vector<lint> v;
	lint ret = 0;
	for(auto &i : mp){
		nitr++;
		tcnt += i.second;
		if(tcnt > 0 && nitr != mp.end()){
			ret += b * (nitr->first - i.first);
		}
		if(tcnt > 0){
			v.push_back(i.first);
			v.push_back(nitr->first);
		}
	}
	sort(strips.begin(), strips.end());
	for(int i=0; i<strips.size(); ){
		int e = i;
		while(e < strips.size() && strips[e].fuck == strips[i].fuck) e++;
		auto l = lower_bound(v.begin(), v.end(), strips[i].fuck + 1) - v.begin();
		if(l % 2 == 1){
			i = e;
			continue;
		}
		int cnt = 0;
		for(int j = i; j + 1 < e; j++){
			cnt += strips[j].dx;
			if(cnt > 0) ret += strips[j + 1].pos - strips[j].pos;
		}
		i = e;
	}
	cout << ret << endl;
}
