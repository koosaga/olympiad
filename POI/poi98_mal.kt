import java.util.*
import java.math.*
import kotlin.system.*
val inf = 987654321

fun main(args : Array<String>){
	val n = readLine()!!.toInt()
	val ta = BigInteger(readLine()!!)
	val tb = BigInteger(readLine()!!)
	val a = Array(n + 1) { if(ta.testBit(it)) 1 else 0 }
	val b = Array(n + 1) { if(tb.testBit(it)) 1 else 0 }
	if(a[n] == 1 || b[n] == 1){
		println("0")
		exitProcess(0)
	}
	val dp = Array(n + 1) { Array(2){ Array(2) { BigInteger.ZERO } } }
	dp[0][0][0] = BigInteger("1");
	for (i in 0..(n-1)){
		for (xc in 0..1){
			for (yc in 0..1){
				for (j in 0..1){
					for (k in 0..1){
						val xsum = (xc + a[i] + j)
						val ysum = (yc + b[i] + k)
						if((ysum % 2) == 1 && j == 1){
							continue
						}
						if((xsum % 2) == 1 && k == 1){
							continue
						}
						dp[i + 1][xsum / 2][ysum / 2] = 
						dp[i + 1][xsum / 2][ysum / 2].add(dp[i][xc][yc])
					}
				}
			}
		}
	}
	println(dp[n][0][0]) 
}

