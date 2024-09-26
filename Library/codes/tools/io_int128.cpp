istream &operator>>(istream &is, __int128_t &v) {
  string s;
  is >> s;
  v = 0;
  for (const auto &i : s) {
    if (isdigit(i)) {
      v = v * 10 + i - '0';
    }
  }
  if (s[0] == '-') {
    v = -v;
  }
  return is;
}

ostream &operator<<(ostream &os, const __int128_t &v) {
  if (!v) {
    return (os << "0");
  }
  __int128_t n = v;
  if (v < 0) {
    os << '-';
    n = -n;
  }
  string s;
  for (; n; n /= 10) {
    s += (n % 10) + '0';
  }
  ranges::reverse(s);
  return (os << s);
}
