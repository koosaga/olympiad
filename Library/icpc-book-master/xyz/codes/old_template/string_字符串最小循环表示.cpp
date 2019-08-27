///////////////////////////
//
// 字符串最小循环表示
//
///////////////////////////
int Min_represent(char *s, int l) {
  int i=0, j=1, k=0, t;
  while (i < l && j < l && k < l) {
    t = s[i + k >= l ? i + k - l : i + k] - s[j + k >= l ? j + k - l : j + k];
    if (!t)  k++;
    else{
      if (t > 0)  i = i + k + 1;
      else  j = j + k + 1;
      if (i == j)  j++;
      k = 0;
    }
  }
  return i < j ? i : j;
}
