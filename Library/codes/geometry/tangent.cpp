int convex_tangent(vector<pi> &C, pi P, int up = 1){
	auto sign = [&](lint c){ return c > 0 ? up : c == 0 ? 0 : -up; };
	auto local = [&](pi P, pi a, pi b, pi c) {
		return sign(ccw(P, a, b)) <= 0 && sign(ccw(P, b, c)) >= 0;
	};
	int N = C.size()-1, s = 0, e = N, m;
	if( local(P, C[1], C[0], C[N-1]) ) return 0;
	while(s+1 < e){
		m = (s+e) / 2;
		if( local(P, C[m-1], C[m], C[m+1]) ) return m;
		if( sign(ccw(P, C[s], C[s+1])) < 0){ // up
			if( sign(ccw(P, C[m], C[m+1])) > 0) e = m;
			else if( sign(ccw(P, C[m], C[s])) > 0) s = m;
			else e = m;
		}
		else{ // down
			if( sign(ccw(P, C[m], C[m+1])) < 0) s = m;
			else if( sign(ccw(P, C[m], C[s])) < 0) s = m;
			else e = m;
		}
	}
	if( s && local(P, C[s-1], C[s], C[s+1]) ) return s;
	if( e != N && local(P, C[e-1], C[e], C[e+1]) ) return e;
	return -1;
}
