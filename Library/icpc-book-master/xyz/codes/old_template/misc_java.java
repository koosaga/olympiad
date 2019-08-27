///////////////////////////
//
// Java
//
///////////////////////////
import java.math.BigInteger;
import java.util.*;

public class prob4 {
  void run() {
    Scanner scanner = new Scanner(System.in);
    while (scanner.hasNextBigInteger()) {
      BigInteger n = scanner.nextBigInteger();
      int k = scanner.nextInt();
      if (k == 0) {
        for (int p = 2; p <= 100000; p++) {
          BigInteger bp = BigInteger.valueOf(p);
          if (n.mod(bp).equals(BigInteger.ZERO)) {
            System.out.println(bp.toString() + " * " + n.divide(bp).toString());
            break;
          }
        }
      } else {
        BigInteger ndivk = n.divide(BigInteger.valueOf(k));
        BigInteger sqndivk = sqrt(ndivk);
        BigInteger left = sqndivk.subtract(BigInteger.valueOf(100000)).max(BigInteger.valueOf(2));
        BigInteger right = sqndivk.add(BigInteger.valueOf(100000));
        for (BigInteger p = left; p.compareTo(right) != 1; p = p.add(BigInteger.ONE)) {
          if (n.mod(p).equals(BigInteger.ZERO)) {
            BigInteger q = n.divide(p);
            System.out.println(p.toString() + " * " + q.toString());
            break;
          }
        }
      }
    }
  }
  BigInteger sqrt(BigInteger n) {
    BigInteger left = BigInteger.ZERO;
    BigInteger right = n;
    while (left.compareTo(right) != 1) {
      BigInteger mid = left.add(right).divide(BigInteger.valueOf(2));
      int s = n.compareTo(mid.multiply(mid));
      if (s == 0) return mid;
      if (s > 0) left = mid.add(BigInteger.ONE); else right = mid.subtract(BigInteger.ONE);
    }
    return right;
  }
  public static void main(String[] args) {
    (new prob4()).run();
  }
}
