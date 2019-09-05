const int MAXN = 1000005;
int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
void solve(int n, char *str, int *sfx, int *rev, int *lcp){
	int p = 1;
	memset(ord, 0, sizeof(ord));
	for(int i=0; i<n; i++){
		sfx[i] = i;
		ord[i] = str[i];
	}
	int pnt = 1;
	while(1){
		memset(cnt, 0, sizeof(cnt));
		for(int i=0; i<n; i++) cnt[ord[min(i+p, n)]]++;
		for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
		for(int i=n-1; i>=0; i--)
			aux[--cnt[ord[min(i+p, n)]]] = i;
		memset(cnt, 0, sizeof(cnt));
		for(int i=0; i<n; i++) cnt[ord[i]]++;
		for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
		for(int i=n-1; i>=0; i--)
			sfx[--cnt[ord[aux[i]]]] = aux[i];
		if(pnt == n) break;
		pnt = 1;
		nord[sfx[0]] = 1;
		for(int i=1; i<n; i++){
			if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
				pnt++;
			}
			nord[sfx[i]] = pnt;
		}
		memcpy(ord, nord, sizeof(int) * n);
		p *= 2;
	}
	for(int i=0; i<n; i++) rev[sfx[i]] = i;
	int h = 0;
	for(int i=0; i<n; i++){
		if(rev[i]){
			int prv = sfx[rev[i] - 1];
			while(str[prv + h] == str[i + h]) h++;
			lcp[rev[i]] = h;
		}
		h = max(h-1, 0);
	}
}
