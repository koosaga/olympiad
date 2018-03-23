import java.util.*
import java.math.BigInteger
import kotlin.math.*

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	var tc = nextInt()
	for (i in 1..tc){
		var pat = next().toCharArray()
		var str = next()
		var ans = '!'
		for (i in 0..(pat.size - 1)){
			if(pat[i] == '_'){
				for(j in 'A'..'Z'){
					pat[i] = j
					if(Regex(pat.joinToString("")).matches(str)){
						if(ans != '!'){
							ans = '_'
							break
						}
						ans = j
					}
				}
			}
		}
		println(ans.toString())
	}
}
