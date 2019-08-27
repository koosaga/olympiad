///////////////////////////
//
// zeller
//
///////////////////////////
int dow(int y, int m, int d) {
  if (m <= 2) y--, m += 12;
  int c = y/100;
  y %= 100;
  int w = (c/4 - c*2 + y + y/4 + 13*(m+1)/5 + d - 1)%7;
  if (w <= 0) w += 7;
  return w;
}

int getId(int y, int m, int d) {
  if (m < 3) {y --; m += 12};
  return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m + 2) / 5 + d;
}
