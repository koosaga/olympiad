///////////////////////////
//
// x^2=n (mod p)
//
///////////////////////////
int Pow(int x, int y, int z) {
  int ans = 1;
  for (int i = 1; i <= y; i *= 2, x = 1LL * x * x % z)  if (i & y)  ans = 1LL * ans * x % z;
  return ans;
}

long long solve(int x, int p) {
  long long b = (1LL * p * p - 1LL * x * x + 3 * x + 1) % (1LL * p * p) / p, a = (2LL * x * p - 3 * p) % (1LL * p * p) / p;
  b = (b + p) % p;
  a = (a + p) % p;
  if (!a) {
    if (!b)  return x;
    else  return 1000000000000000000LL;
  }else  return 1LL * b * Pow(a, p - 2, p) % p * p + x;
}

long long solve2(int x, int p) {
  if ((x + 3) % 2 == 0)  return solve((x + 3) / 2, p);
  else  return solve((x + 3 + p) / 2, p);
}

long long solve1(long long p, long long n) {
  if (Pow(n, (p - 1) / 2, p) != 1)  return 1000000000000000000LL;
  long long Q, S, z, R, t, M, c, b;
  for (Q = p - 1, S = 0; Q % 2 == 0; Q /= 2, S++);
  for (z = 1; Pow(z, (p - 1) / 2, p) == 1; z++);
  c = Pow(z, Q, p);
  R = Pow(n, (Q + 1) / 2, p);
  t = Pow(n, Q, p);
  M = S;
  while (t != 1) {
    long long i;
    for (i = 1; i < M; i++)  if (Pow(t, (1 << i), p) == 1)  break;
    b = Pow(c, (1 << (M - i - 1)), p);
    R = R * b % p;
    t = t * b % p * b % p;
    c = b * b % p;
    M = i;
  }
  return min(solve2(R, p), solve2(p - R, p));
}
