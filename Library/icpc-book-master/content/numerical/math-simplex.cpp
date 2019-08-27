/**
 * Author: 
 * Description: Simplex algorithm.
 * WARNING-  segfaults on empty (size 0)
 * max cx st Ax<=b, x>=0
 * do 2 phases; 1st check feasibility;
 * 2nd check boundedness and ans
 */
vector<double> simplex(vector<vector<double> > A, vector<double> b, vector<double> c) {
  int n = (int) A.size(), m = (int) A[0].size()+1, r = n, s = m-1; 
  vector<vector<double> > D = vector<vector<double> > (n+2, vector<double>(m+1)); 
  vector<int> ix = vector<int> (n+m); 
  for (int i=0; i<n+m; i++) ix[i] = i; 
  for (int i=0; i<n; i++) {
    for (int j=0; j<m-1; j++)D[i][j]=-A[i][j]; 
    D[i][m-1] = 1; 
    D[i][m] = b[i]; 
    if (D[r][m] > D[i][m]) r = i; 
  }
  for (int j=0; j<m-1; j++) D[n][j]=c[j]; 
  D[n+1][m-1] = -1; int z = 0; 
  for (double d;;) {
    if (r < n) {
      swap(ix[s], ix[r+m]); 
      D[r][s] = 1.0/D[r][s]; 
      for (int j=0; j<=m; j++) if (j!=s) D[r][j] *= -D[r][s]; 
      for(int i=0; i<=n+1; i++)if(i!=r) {
        for (int j=0; j<=m; j++) if(j!=s) D[i][j] += D[r][j] * D[i][s]; 
        D[i][s] *= D[r][s]; 
      }
    }
    r = -1; s = -1; 
    for (int j=0; j <m; j++) if (s<0 || ix[s]>ix[j]) {
      if (D[n+1][j]>eps || D[n+1][j]>-eps && D[n][j]>eps) s = j; 
    }
    if (s < 0) break; 
    for (int i=0; i<n; i++) if(D[i][s]<-eps) {
      if (r < 0 || (d = D[r][m]/D[r][s]-D[i][m]/D[i][s]) < -eps
        || d < eps && ix[r+m] > ix[i+m]) r=i; 
    }
    if (r < 0) return vector<double>(); // unbounded
  }
  if (D[n+1][m] < -eps) return vector<double>(); // infeasible
  vector<double> x(m-1); 
  for (int i = m; i < n+m; i ++) if (ix[i] < m-1) x[ix[i]] = D[i-m][m];
  printf("%.2lf\n", D[n][m]); 
  return x; // ans: D[n][m]
}