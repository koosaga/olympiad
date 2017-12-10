import java.util.*

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
    var n = nextInt()
    var m = nextInt()
    println(n/2 + m/2)
    for (i in 2..n step 2){
        println(i.toString() + " 1 " + i.toString() + " " + m.toString());
    }
    for (i in 2..m step 2){
        println("1 " + i.toString() + " " + n.toString() + " " + i.toString());
    }
}
