
const int MAXN = 105;
struct matrix{
	lint adj[MAXN][MAXN];
	int n;
	matrix(int _n, int c){
		n = _n;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				adj[i][j] = (i == j ? c : 0);
			}
		}
	}
	matrix operator*(const matrix &a)const{
		matrix c(n, 0);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					c.adj[j][k] += adj[j][i] * a.adj[i][k] % mod;
					c.adj[j][k] %= mod;
				}
			}
		}
		return c;
	}
	matrix operator+(const matrix &a)const{
		matrix c(n, 0);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				c.adj[i][j] = (adj[i][j] + a.adj[i][j]) % mod;
			}
		}
		return c;
	}
	matrix operator-(const matrix &a)const{
		matrix c(n, 0);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				c.adj[i][j] = (adj[i][j] + mod - a.adj[i][j]) % mod;
			}
		}
		return c;
	}
};
