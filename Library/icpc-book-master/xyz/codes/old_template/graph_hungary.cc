///////////////////////////
//
// Hungarian
//
///////////////////////////
bool fi(int k) {
  for (int j = 0; j < m; j++)
    if (ok[k][j] && used[j] < Time) {
      used[j] = Time;
      if (Link[j] < 0 || fi(Link[j])) {
        Link[j] = k;
        return true;
      }
    }
  return false;
}
