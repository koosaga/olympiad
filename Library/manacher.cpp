const int MAXN = 1000005;
struct manacher{
	int aux[2 * MAXN - 1];
	void solve(int n, int *str, int *ret){
		for(int i=0; i<n; i++){
			aux[2*i] = str[i];
			if(i != n-1) aux[2*i+1] = -1;
		}
		int p = 0, c = 0;
		for(int i=0; i<2*n-1; i++){
			int cur = 0;
			if(i <= p) cur = min(ret[2 * c - i], p - i);
			while(i - cur - 1 >= 0 && i + cur + 1 < 2*n-1 && aux[i-cur-1] == aux[i+cur+1]){
				cur++;
			}
			ret[i] = cur;
			if (i + cur >= p) {
				p = i + cur, c = i;
			}
		}
	}
}manacher;
