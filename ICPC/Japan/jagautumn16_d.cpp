#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

struct node{
	string literalV;
	int feedT;
	lint constV;
	lint feedV;
	lint multV;
};

void dbg(node new_node){
	printf("literalV = %s type = %d constV = %lld feedV = %lld multV = %lld\n", new_node.literalV.c_str(), new_node.feedT, new_node.constV, new_node.feedV, new_node.multV);

}
node FEED(node x, char c){
	if(c == '+'){
		if(x.feedT == -1){
			for(auto &i : x.literalV){
				x.constV = (x.constV * 10 + i - '0') % mod;
			}
			x.literalV.clear();
		}
		if(x.feedT == 0){ // add
			x.constV += x.feedV;
		}
		if(x.feedT == 1){
			x.constV += mod - x.feedV;
		}
		if(x.feedT == 2){
			x.constV += x.multV * x.feedV;
		}
		x.multV = 0;
		x.feedV = 0;
		x.feedT = 0;
	}
	else if(c == '-'){
		if(x.feedT == -1){
			for(auto &i : x.literalV){
				x.constV = (x.constV * 10 + i - '0') % mod;
			}
			x.literalV.clear();
		}
		if(x.feedT == 0){ // add
			x.constV += x.feedV;
		}
		if(x.feedT == 1){
			x.constV += mod - x.feedV;
		}
		if(x.feedT == 2){
			x.constV += x.multV * x.feedV;
		}
		x.multV = 0;
		x.feedV = 0;
		x.feedT = 1;
	}
	else if(c == '*'){
		if(x.feedT == -1){
			for(auto &i : x.literalV){
				x.constV = (x.constV * 10 + i - '0') % mod;
			}
			x.literalV.clear();
		}
		if(x.feedT == 0){ // add
			x.multV = x.feedV;
		}
		if(x.feedT == 1){
			x.multV = mod - x.feedV;
		}
		if(x.feedT == 2){
			x.multV *= x.feedV;
		}
		x.feedV = 0;
		x.feedT = 2;
	}
	else{
		if(x.feedT == -1){
			x.literalV.push_back(c);
		}
		else x.feedV = x.feedV * 10 + (c - '0');
	}
	x.constV %= mod;
	x.multV %= mod;
	x.feedV %= mod;
	return x;
}

node MERGE(node l, node r){
	puts("dbging");
	dbg(l);
	dbg(r);
	for(auto &i : r.literalV){
		l = FEED(l, i);
	}
	l = FEED(l, '+');
	l.constV += r.constV; // assert l.feedT = 0
	l.feedT = r.feedT;
	l.multV = r.multV;
	l.feedV = r.feedV;
	dbg(l);
	puts("end");
	return l;
}

node POWER(node x, int p){
	if(p == 1) return x;
	if(p & 1) return MERGE(POWER(x, p - 1), x);
	return POWER(MERGE(x, x), p / 2);
}

lint READ(node x){
	lint tmp = 0;
	for(auto &i : x.literalV){
		tmp = (tmp * 10 + i - '0')% mod;
	}
	x.constV += tmp;
	if(x.feedT <= 0) return (x.constV + x.feedV) % mod;
	if(x.feedT == 1) return (x.constV + mod - x.feedV) % mod;
	if(x.feedT == 2) return (x.constV + x.multV * x.feedV) % mod;
	assert(0);
}


int main(){
	int n; cin >> n;
	node nd = {"", -1, 0, 0, 0};
	for(int i=0; i<n; i++){
		int x; string s; cin >> x >> s;
		node new_node = {"", -1, 0, 0, 0};
		for(auto &k : s){
			new_node = FEED(new_node, k);
		}
		dbg(new_node);
		puts("good");
		new_node = POWER(new_node, x);
		nd = MERGE(nd, new_node);
	}
	cout << READ(nd) << endl;
}
