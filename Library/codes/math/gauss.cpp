int n, inv;
vector<int> basis[505];
lint gyesu = 1;

void insert(vector<int> v){
	for(int i=0; i<n; i++){
		if(basis[i].size()) inv ^= 1; // inversion num increases
		if(v[i] && basis[i].empty()){
			basis[i] = v;
			return;
		}
		if(v[i]){
			lint minv = ipow(basis[i][i], mod - 2) * v[i] % mod;
			for(auto &j : basis[i]) j = (j * minv) % mod;
			gyesu *= minv;
			gyesu %= mod;
			for(int j=0; j<basis[i].size(); j++){
				v[j] += mod - basis[i][j];
				while(v[j] >= mod) v[j] -= mod;
			}
		}
	}
	puts("0");
	exit(0);
}

// Sample: Calculates Determinant in Z_p Field
int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		vector<int> v(n);
		for(int j=0; j<n; j++) scanf("%d",&v[j]);
		if(i % 2 == 1) inv ^= 1;
		insert(v);
	}
	if(inv) gyesu = mod - gyesu;
	gyesu = ipow(gyesu, mod - 2);
	for(int i=0; i<n; i++) gyesu = gyesu * basis[i][i] % mod;
	cout << gyesu % mod << endl; 
}