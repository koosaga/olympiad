#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using real_t = long double;
using pi = complex<real_t>;
const bool POINT = 0;
const bool LINE = 1;

struct prmtv{
	bool TYPE;
	pi p; // point
	real_t a, b, c;
};

prmtv OP(prmtv A, prmtv B){
	if(A.TYPE > B.TYPE) swap(A, B);
	if(A.TYPE == POINT && B.TYPE == POINT){
		pi dir = B.p - A.p;
		prmtv C;
		C.TYPE = LINE;
		C.a = dir.imag();
		C.b = -dir.real();
		C.c = C.a * A.p.real() + C.b * A.p.imag();
		return C;
	}
	if(A.TYPE == LINE && B.TYPE == LINE){
		real_t det = A.a * B.b - B.a * A.b;
		real_t xc = B.b * A.c  - A.b * B.c;
		real_t yc = A.a * B.c  - A.c * B.a;
		prmtv C;
		C.TYPE = POINT;
		C.p = pi(xc / det, yc / det);
		return C;
	}
	// printf("daeching %.10Lf %.10Lf to %.10Lfx + %.10Lfy = %.10Lf\n", A.p.real(), A.p.imag(), B.a, B.b, B.c);
	real_t dist = (B.a * A.p.real() + B.b * A.p.imag() - B.c) / hypot(B.a, B.b);
	dist *= 2;
	prmtv C;
	C.TYPE = POINT;
	C.p = A.p - (pi(B.a, B.b) / hypot(B.a, B.b)) * dist;
	//printf("%.10Lf %.10Lf is result\n", C.p.real(), C.p.imag());
	return C;
}

int ptr;
string str;

int num_parse(int s){
	if(str[s] == '-') return num_parse(s + 1) * -1;
	int ret = 0;
	for(int j=s; isdigit(str[j]); j++){
		ret = ret * 10 + str[j] - '0';
		ptr = j + 1;
	}
	return ret;
}

prmtv Point(int s){
	if(s >= str.size()) assert(0);
	//printf("parsing %s\n", str.substr(s, str.size() - s).c_str());

	if(str[s + 1] == '-' || isdigit(str[s + 1])){
		// ( , )
		int x = num_parse(s + 1);
		int y = num_parse(ptr + 1);
		ptr++;
		prmtv ret;
		ret.TYPE = POINT, ret.p = pi(x, y);
		return ret;
	}
	else{
		ptr = s;
		vector<prmtv> v;
		while(true){
	//		printf("let parse %s\n", str.substr(ptr + 1, str.size()-ptr-1).c_str());
			v.push_back(Point(ptr + 1));
	//		printf("got the results, next = %s\n", str.substr(ptr, str.size() - ptr).c_str());
			if(str[ptr] == ')') break;
		}
		for(int i=1; i<v.size(); i++) v[0] = OP(v[0], v[i]);
		ptr++;
		return v[0];
	}
}

int main(){
	while(true){
		cin >> str;
		if(str == "#") break;
		str = "(" + str + ")";
		ptr = 0;
		auto x = Point(0).p;
		printf("%.10Lf %.10Lf\n", x.real(), x.imag());
	}
}
