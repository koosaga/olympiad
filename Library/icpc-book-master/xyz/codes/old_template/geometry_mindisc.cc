///////////////////////////
//
// mindisc
//
///////////////////////////
P getC(P a, P b, P c) {
  db aa = (b-c).abs2(), bb = (a-c).abs2(), cc = (a-b).abs2();
  db wa = aa*(bb+cc-aa);
  db wb = bb*(aa+cc-bb);
  db wc = cc*(aa+bb-cc);
  return (a*wa+b*wb+c*wc)/(wa+wb+wc);
}

double ff() {
  random_shuffle(b, b+n);
  P o = b[0];
  double R = 0;
  for (int i = 1; i < n; i ++) if (o.dis(b[i]) > R + eps) {
    o = b[i];
    R = 0;
    for (int j = 0; j < i; j ++) if (o.dis(b[j]) > R + eps) {
      o = (b[i] + b[j])*0.5;
      R = o.dis(b[j]);
      for (int k = 0; k < j; k ++) if (o.dis(b[k]) > R + eps) {
        o = getC(b[i], b[j], b[k]);
        R = o.dis(b[k]);
      }
    }
  }
  return R;
}
