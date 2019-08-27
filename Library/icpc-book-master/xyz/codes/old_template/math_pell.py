###################
#
#  Pell equation
#
###################
def pell(n):
  p1 = q0 = h1 = 1
  p0 = q1 = g1 = 0
  a2 = int(math.floor(math.sqrt(n)+1e-7))
  if a2*a2 == n:
    return (-1, -1)
  ai = a2
  ii = 1
  while True:
    ii += 1
    g1 = -g1 + ai*h1
    h1 = (n - g1*g1)/h1
    p0, p1 = p1, ai*p1 + p0
    q0, q1 = q1, ai*q1 + q0
    ai = (g1 + a2)/h1
    
    if p1*p1 - n*q1*q1 == 1:
      print ii
      return (p1, q1)
