///////////////////////////
//
// 树状数组二分
// Find the smallest 1 <= x <= n such that sigma_i^x a_i >= y
// Make sure n = 2^lim
///////////////////////////

int getit(int y)
{
  int x = 0, i;
  for (i=lim2;i>=0;i--) {
    x+=(1<<i);
    if (b[x]>=y)  x-=(1<<i);
    else  y-=b[x];
  }
  return x+1;
}
