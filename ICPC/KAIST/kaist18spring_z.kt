import kotlin.math.*
import java.util.*
import java.math.*

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	var n = nextInt()
	var a = Array(n) { nextInt() } 
	var ans = 2
	for (i in 0..(n-1)){
		var las = i + 1
		for (j in (i+2)..(n-1)){
			var ok1 = (a[j-1] < a[j]) && (a[j-2] > a[j-1]);
			var ok2 = (a[j-1] > a[j]) && (a[j-2] < a[j-1]);
			if(!(ok1 || ok2)){
				break;
			}
			las = j;
		}
		ans = max(ans, las - i + 1);
	}
	println(ans)
}
