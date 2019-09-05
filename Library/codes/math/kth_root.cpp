/* 
 * Solve x for x^P = A mod Q
 * (P, Q-1) = 1 -> P^-1 mod (Q-1) exists
 * x has solution iff A^((Q-1) / P) = 1 mod Q
 * PP | (Q-1) -> P < sqrt(Q), solve lgQ rounds of discrete log
 * else -> find a s.t. s | (Pa - 1) -> ans = A^a */
using LL = long long;
LL mul(LL x, LL y, LL mod){ return (__int128) x * y % mod; }
LL add(LL x, LL y, LL mod){ return (x + y) % mod; }
LL pw(LL x, LL y, LL mod){
	LL ret = 1, piv = x;
	while(y){
		if(y & 1) ret = mul(ret, piv, mod);
		piv = mul(piv, piv, mod);
		y >>= 1;
	}
	return ret % mod;
}
void gcd(LL a, LL b, LL &x, LL &y, LL &g){
	if (b == 0) {
		x = 1, y = 0, g = a;
		return;
	}
	LL tx, ty;
	gcd(b, a%b, tx, ty, g);
	x = ty; y = tx - ty * (a / b);
}
LL P, A, Q, g; // x^P = A mod Q
const int X = 1e5;
LL base, ae[X], aXe[X], iaXe[X];
unordered_map<LL, LL> ht;
#define FOR(i, c) for (int i = 0; i < (c); ++i)
#define REP(i, l, r) for (int i = (l); i <= (r); ++i)
void build(LL a) { // ord(a) = P < sqrt(Q)
	base = a;
	ht.clear();
	ae[0] = 1; ae[1] = a; aXe[0] = 1; aXe[1] = pw(a, X, Q);
	iaXe[0] = 1; iaXe[1] = pw(aXe[1], Q-2, Q);
	REP(i, 2, X-1) {
		ae[i] = mul(ae[i-1], ae[1], Q);
		aXe[i] = mul(aXe[i-1], aXe[1], Q);
		iaXe[i] = mul(iaXe[i-1], iaXe[1], Q);
	}
	FOR(i, X) ht[ae[i]] = i;
}

LL dis_log(LL x) {
	FOR(i, X) {
		LL iaXi = iaXe[i];
		LL rst = mul(x, iaXi, Q);
		if (ht.count(rst)) return i*X + ht[rst];
	}
}
LL main2() {
		cin >> P >> A >> Q;
	LL t = 0, s = Q-1;
	while (s % P == 0) {
		++t;
		s /= P;
	}
	if (A == 0) return 0;
	if (t == 0) {
		// a^{P^-1 mod phi(Q)}
		LL x, y, _;
		gcd(P, Q-1, x, y, _);
		if (x < 0) {
			x = (x % (Q-1) + Q-1) % (Q-1);
		}
		LL ans = pw(A, x, Q);
		if (pw(ans, P, Q) != A) while(1);
		return ans;
	}
	// A is not P-residue
	if (pw(A, (Q-1) / P, Q) != 1) return -1;
	for (g = 2; g < Q; ++g) {
		if (pw(g, (Q-1) / P, Q) != 1)
			break;
	}
	LL alpha = 0;
	{
		LL y, _;
		gcd(P, s, alpha, y, _);
		if (alpha < 0) alpha = (alpha % (Q-1) + Q-1) % (Q-1);
	}
	if (t == 1) {
		LL ans = pw(A, alpha, Q);
		return ans;
	}
	LL a = pw(g, (Q-1) / P, Q);
	build(a);
	LL b = pw(A, add(mul(P%(Q-1), alpha, Q-1), Q-2, Q-1), Q);
	LL c = pw(g, s, Q);
	LL h = 1;
	LL e = (Q-1) / s / P; // r^{t-1}
	REP(i, 1, t-1) {
		e /= P;
		LL d = pw(b, e, Q);
		LL j = 0;
		if (d != 1) {
			j = -dis_log(d);
			if (j < 0) j = (j % (Q-1) + Q-1) % (Q-1);
		}
		b = mul(b, pw(c, mul(P%(Q-1), j, Q-1), Q), Q);
		h = mul(h, pw(c, j, Q), Q);
		c = pw(c, P, Q);
	}
	return mul(pw(A, alpha, Q), h, Q);
}
