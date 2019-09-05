class SuffixArray {
public:
	int A[7 * N / 10], B[7 * N / 10], cnt[N + 2], SAV[N];
	int mem[5 * N]; int* mem_pt = mem;
	void clear(int n){
		int *ptr = mem;
		while(ptr != mem_pt){
			*ptr = 0;
			ptr++;
		}
		mem_pt = mem;
		for(int i=0; i<n+10 && i < 7 * N / 10; i++) A[i] = B[i] = 0;
		for(int i=0; i<n+2; i++) cnt[i] = 0;
		for(int i=0; i<n; i++) SAV[i] = 0;
	}
	inline int* mloc(size_t sz) {
		int* ret = mem_pt; mem_pt = mem_pt + sz;
		return ret;
	}
	void rsort(int* a, int* b, int* dat, int n, int k) { 
		for (int i = 0; i <= k; i++) cnt[i] = 0;
		for (int i = 0; i < n; i++) SAV[i] = dat[a[i]], cnt[SAV[i]]++;
		for (int i = 1; i <= k; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) b[--cnt[SAV[i]]] = a[i];
	}

#define I(x) ((x)%3==1)?((x)/3):((x)/3+num1)
#define I2(x) (x<num1)?(3*x+1):(3*(x-num1)+2)
	static int cmp(int x, int y, int str[], int A[], int num1) {
		if (x % 3 == 1) {
			if (y % 3 == 2) return A[I(x)] < A[I(y)];
			else return str[x] < str[y] || str[x] == str[y] && A[I(x + 1)] < A[I(y + 1)];
		}
		else {
			return str[x] < str[y] || str[x] == str[y] && cmp(x + 1, y + 1, str, A, num1);
		}
	}
	void make(int* str, int* sa, int n, int k) {
		if (n == 0) return;
		int num1 = (n + 2) / 3, num2 = n / 3;
		int num = num1 + num2;
		str[n] = str[n + 1] = str[n + 2] = 0;
		int *nsa = mloc(num), *nstr = mloc(num + 3);

		for (int i = 0, j = 0; i < n; i++) if (i % 3) A[j++] = i;
		if (n % 3 == 1) A[num - 1] = n;
		rsort(A, B, str + 2, num, k); rsort(B, A, str + 1, num, k); rsort(A, B, str, num, k);

		int cnt = 1;
		nstr[I(B[0])] = 1;
		for (int i = 1; i < num; i++) {
			int c = B[i], p = B[i - 1];
			if (str[p] != str[c] || str[p + 1] != str[c + 1] || str[p + 2] != str[c + 2]) cnt++;
			nstr[I(c)] = cnt;
		}
		if (cnt == num) for (int i = 0; i < num; i++) nsa[nstr[i] - 1] = i;
		else make(nstr, nsa, num, cnt);
		
		for (int i = 0, j = 0; i < num; i++) if (nsa[i] < num1) A[j++] = 3 * nsa[i];
		rsort(A, B, str, num1, k);
		for (int i = 0; i < num; i++) A[nsa[i]] = i, nsa[i] = I2(nsa[i]);
		A[num] = -1;
		merge(B, B + num1, nsa + (n % 3 == 1), nsa + num, sa, [&](int x, int y) {
			return cmp(x, y, str, A, num1); 
		});
		return;
	}
}sa;
