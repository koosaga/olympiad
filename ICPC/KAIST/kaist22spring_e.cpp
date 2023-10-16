#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const bool dbg = 0;
const lint infty = 1000000000;

vector<lint> v;

void solve(){
	int op = 0;
	auto add = [&](int a, int b, int c){
		if(dbg){
			v[a] = v[b] + v[c];
			if(v[a] > infty){
				cout << a << " " << b << " " << c << endl;
			}
			assert(v[a] <= infty);
		}
		else{
			cout << "+ " << a+1 << " " << b+1 << " " << c+1 << endl;
		}
		op++;
	};
	auto sub = [&](int a, int b, int c){
		if(dbg){
			v[a] = v[b] - v[c];
			assert(v[a] >= 0);
		}
		else{
			cout << "- " << a+1 << " " << b+1 << " " << c+1 << endl;
		}
		op++;
	};
	auto comp = [&](int a, int b){
		op++;
		if(dbg){
			if(v[a] < v[b]) return -1;
			if(v[a] > v[b]) return 1;
			return 0;
		}
		else{
			cout << "< " << a+1 << " " << b+1 << endl;
			int q; cin >> q; return q;
		}
	};
	auto Swap = [&](int x, int y){
		add(98, 99, x);
		add(x, y, 99);
		add(y, 98, 99);
	};
	int step = 0;
	while(true){
		step++;
	//	if(dbg) cout << "step: " << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << endl;
		add(4, 1, 99);
		add(50, 3, 99);
		int tx = 4;
		int ty = 50;
		for(int i = 5; i < 35; i++){
			if(step <= 4){
				// touch doldary before cross
				if(i == 5 && comp(0, i-1) == -1){
					ty = i - 1;
					break;
				}
				sub(97, 0, i-1);
				if(comp(97, i-1) == -1){
					tx = i - 1;
					break;
				}
			}
			add(i, i-1, i-1);
			int c = comp(0, i);
			if(c != 1){
				tx = i-1 + (c == 0);
				break;
			}
		}
		for(int i = 51; i < 81; i++){
			if(step <= 4){
				// touch doldary before cross
				if(i == 51 && comp(2, i-1) == -1){
					ty = i - 1;
					break;
				}
				sub(97, 2, i-1);
				if(comp(97, i-1) == -1){
					ty = i - 1;
					break;
				}
			}
			add(i, i-1, i-1);
			int c = comp(2, i);
			if(c != 1){
				ty = i-1 + (c == 0);
				break;
			}
		}
		bool hasRem1 = 1;
		bool hasRem2 = 1;
		int mok1 = 0;
		int mok2 = 0;
		for(int i = tx; i >= 4; i--){ 
			int query = comp(0, i);
			if(query == -1) continue;
			sub(0, 0, i);
			mok1 += (1ll << (i-4));
			if(query == 0) hasRem1 = 0;
		}
		for(int i = ty; i >= 50; i--){ 
			int query = comp(2, i);
			if(query == -1) continue;
			sub(2, 2, i);
			mok2 += (1ll << (i-50));
			if(query == 0) hasRem2 = 0;
		}
		if(pi(mok1, hasRem1) != pi(mok2, hasRem2)){
		//	if(dbg) cout << mok1 << " " << hasRem1 << " " << mok2 << " " << hasRem2 << endl;
			int verd = pi(mok1, hasRem1) < pi(mok2, hasRem2);
			cout << "! " << (1 - verd * 2) << endl;
			break;
		}
		if(hasRem1 == 0 && hasRem2 == 0){
			cout << "! 0" << endl;
			break;
		}
		Swap(0, 3);
		Swap(1, 2);
	}
	if(dbg) cout << op << endl;
}

mt19937 rng(0x1557);

int randint(int n){
	std::uniform_int_distribution<> distrib(1, n);
	return distrib(rng);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	v.resize(100);
	if(dbg){
		int q; cin >> q;
		for(int i = 0; i < q; i++){
			fill(all(v), 0);
			v[0] = randint(1e9);
			v[1] = randint(1e9);
			v[2] = v[0];
			v[3] = v[1];
			//randint(1e9);
		//	v[3] = randint(1e9);
			cout << (v[0] * v[3] < v[1] * v[2] ? "! -1" : "! 1") << endl;
			solve();
			cout << endl;
		}
	}
	else{
		solve();
	}
}
