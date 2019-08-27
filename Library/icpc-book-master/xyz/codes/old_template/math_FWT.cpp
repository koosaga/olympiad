////////////////////////
//
// FWT
//
//////////////////////////
XOR:
tf(A)=(tf(A0)+tf(A1),tf(A0)−tf(A1))
utf(A)=(utf((A0+A1)/2),utf((A0−A1)/2))
AND:
tf(A)=(tf(A0)+tf(A1),tf(A1))
utf(A)=(utf(A0)−utf(A1),utf(A1))
OR:
tf(A)=(tf(A0),tf(A1)+tf(A0))
utf(A)=(utf(A0),utf(A1)−utf(A0))

Example, AND:
void FWT( ll X[], int l, int r, int v ) {
  if ( l == r ) return;
  int m = ( l + r ) >> 1;
  FWT( X, l, m, v ); FWT( X, m + 1, r, v );
  FOR ( i, 0, m - l ) {
    X[ l + i ] += X[ m + 1 + i ] * v;
  }
}
