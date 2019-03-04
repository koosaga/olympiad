import kotlin.math.*
import java.util.*

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	while(true){
		var n = readLine()!!.toInt()
		if(n == 0) break
		var ans = 0
		for (i in 1..n){
			if(i > 2000) break
			if(i % 2 == 1){
				if(n % i != 0) continue
				if(n / i - i / 2 > 1) ans++
			}
			else{
				if(n % (i / 2) != 0) continue
				var avg = n / (i / 2)
				if(avg % 2 == 0) continue
				if(avg / 2 - i / 2 >= 1) ans++
			}
		}
		println(ans)
	}
}
