import java.util.*
import java.math.BigInteger
import kotlin.math.abs
import kotlin.math.min

var is_mem = Array(101){ Array(401) { Array(2) { false } } }
var mem = Array(101){ Array(401){ Array(2) { BigInteger.ZERO } } }

var n = 0

fun solve(n : Int, sum : Int, prev : Int) : BigInteger{
	if(n == 0) return BigInteger.ONE
	if(is_mem[n][sum][prev]) return mem[n][sum][prev]
	var ans = BigInteger(solve(n - 1, sum, 0).toString())
	if(prev == 0 && sum >= n) ans = ans.add(solve(n - 1, sum - n, 1))
	is_mem[n][sum][prev] = true
	mem[n][sum][prev] = ans
	return ans
}

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	n = nextInt()
	var k = nextInt()
	var subdp = Array(n + 1) { BigInteger.ZERO }
	subdp[0] = BigInteger.ONE
	subdp[1] = BigInteger("2")
	for (i in 2..n){
		subdp[i] = BigInteger(subdp[i-1].toString()).add(subdp[i-2])
	}
	println(subdp[n].subtract(solve(n, k, 0)))
}

