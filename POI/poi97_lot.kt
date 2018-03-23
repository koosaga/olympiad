import java.util.*
import java.math.BigInteger
import kotlin.math.abs
import kotlin.math.min

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	var n = nextInt()
	var v = mutableListOf<Pair<Int, Int>>()
	for (i in 1..n){
		var x = nextInt()
		v.add(Pair(x, i))
	}
	while(v.size > 0){
		v.sortBy{ -it.first }
		for (j in 1..v[0].first){
			v[j] = Pair(v[j].first - 1, v[j].second)
			println(v[j].second.toString() + " " + v[0].second.toString())
		}
		v.removeAt(0)
	}

}

