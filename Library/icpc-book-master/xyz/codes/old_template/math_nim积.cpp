///////////////////////////
//
// nim product
//
///////////////////////////
int _nim(int x, int y) {
  if (!x || !y)  return 1 << (x + y);
  if (f[x][y] != -1)  return f[x][y];
  int ret = 1, e = 1;
  for (int i = 0; i <= 4; i++)
    if ((x ^ y) & (1 << i))  e *= (1 << (1 << i));
    else  if (x & (1 << i))  ret = nim(ret, 3 * (1 << (1 << i)) / 2);
  f[x][y] = nim(ret, e);
  return f[x][y];
}
int nim(int x, int y) {
  int ret = 0;
  for (int i = 0; i <= 20; i++)
    if (x & (1 << i))
      for (int j = 0; j <= 20; j++)
        if (y & (1 << j))  ret ^= _nim(i, j);
  return ret;
}
