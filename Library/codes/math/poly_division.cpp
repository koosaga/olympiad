vector<lint> get_inv(int n, const vector<lint> &p){
	vector<lint> q = {ipow(p[0], mod - 2)};
	for(int i=2; i<=n; i<<=1){
		vector<lint> res;
		vector<lint> fq(q.begin(), q.end()); fq.resize(2*i);
		vector<lint> fp(p.begin(), p.begin() + i); fp.resize(2*i);
		fft(fq, 0); fft(fp, 0);
		for(int j=0; j<2*i; j++){
			fp[j] *= fq[j] * fq[j] % mod;
			fp[j] %= mod;
		}
		fft(fp, 1);
		res.resize(i);
		for(int j=0; j<i; j++){
			res[j] = mod - fp[j];
			if(j < i/2) res[j] += 2 * q[j];
			res[j] %= mod;
		}
		q = res;
	}
	return q;
}
vector<lint> poly_divide(const vector<lint> &a, const vector<lint> &b){
	assert(b.back() != 0); // please trim leading zero
	int n = a.size(), m = b.size();
	int k = 2; while(k < n-m+1) k <<= 1;
	vector<lint> rb(k), ra(k);
	for(int i=0; i<m && i<k; ++i) rb[i] = b[m-i-1];
	for(int i=0; i<n && i<k; ++i) ra[i] = a[n-i-1];
	vector<lint> rbi = get_inv(k, rb);
	vector<lint> res = multiply(rbi, ra);
	res.resize(n - m + 1);
	reverse(res.begin(), res.end());
	return res;
}
