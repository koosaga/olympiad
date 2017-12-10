import java.util.*
import kotlin.math.min

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
    var n = nextInt()
    var q = nextInt()
    var a = IntArray(n) { 0 }
    var b = IntArray(n) { 0 }
    for (i in 0..(n-1)){
        a[i] = nextInt();
        b[i] = nextInt();
    }
    for (i in 1..q){
        var s = nextInt()
        var e = nextInt()
        var t = nextInt()
        var ans = 0
        for (j in 0..(n-1)){
            var intv = b[j] - a[j];
            var curt = (t % (2 * intv))
            curt = min(curt, 2 * intv - curt)
            if(s <= a[j] + curt && a[j] + curt <= e) ans++
        }
        println(ans)
    }
}
