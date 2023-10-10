import kotlin.math.*
import java.util.*
import java.math.*

val yutPan = 
"..----..----..----..----..----..\n..    ..    ..    ..    ..    ..\n| \\                          / |\n|  \\                        /  |\n|   \\                      /   |\n|    ..                  ..    |\n..   ..                  ..   ..\n..     \\                /     ..\n|       \\              /       |\n|        \\            /        |\n|         ..        ..         |\n|         ..        ..         |\n..          \\      /          ..\n..           \\    /           ..\n|             \\  /             |\n|              ..              |\n|              ..              |\n|             /  \\             |\n..           /    \\           ..\n..          /      \\          ..\n|         ..        ..         |\n|         ..        ..         |\n|        /            \\        |\n|       /              \\       |\n..     /                \\     ..\n..   ..                  ..   ..\n|    ..                  ..    |\n|   /                      \\   |\n|  /                        \\  |\n| /                          \\ |\n..    ..    ..    ..    ..    ..\n..----..----..----..----..----.."

var Position = arrayOf(Pair(30, 30), Pair(24, 30), Pair(18, 30), Pair(12, 30), Pair(6, 30), Pair(0, 30), Pair(0, 24), Pair(0, 18), Pair(0, 12), Pair(0, 6), Pair(0, 0), Pair(6, 0), Pair(12, 0), Pair(18, 0), Pair(24, 0), Pair(30, 0), Pair(30, 6), Pair(30, 12), Pair(30, 18), Pair(30, 24), Pair(5, 25), Pair(10, 20), Pair(15, 15), Pair(20, 10), Pair(25, 5), Pair(5, 5), Pair(10, 10), Pair(20, 20), Pair(25, 25))

fun next(pos : Int, nxt : Int) : Int{
	if(pos == -1) return nxt
	if(pos == 0) return -1
	if(pos in 1..4 || pos in 6..9 || pos in 11..19){ 
		if(pos + nxt > 20) return -1
		if(pos + nxt == 20) return 0
		return pos + nxt
	}
	if(pos == 5){ // 5
		return 19 + nxt
	}
	if(pos == 10){ // 10
		return when(nxt){
			1 -> 25
			2 -> 26
			3 -> 22
			4 -> 27
			else -> 28
		}
	}
	if(pos == 22){ // 22
		return when(nxt){
			1 -> 27
			2 -> 28
			3 -> 0
			else -> -1
		}
	}
	if(pos in 20..24){ 
		if(pos + nxt > 24){
			var surplus = pos + nxt - 25
			return 15 + surplus
		}
		return pos + nxt
	}
	return when(pos){
		25 -> when(nxt){
			1 -> 26
			2 -> 22
			3 -> 27
			4 -> 28
			else -> 0
		}
		26 -> when(nxt){
			1 -> 22
			2 -> 27
			3 -> 28
			4 -> 0
			else -> -1
		}
		27 -> when(nxt){
			1 -> 28
			2 -> 0
			else -> -1
		}
		28 -> when(nxt){
			1 -> 0
			else -> -1
		}
		else -> throw IllegalArgumentException()
	}
}

fun main(args : Array<String>){
	val br = java.io.BufferedReader(java.io.InputStreamReader(System.`in`), 32768)
	val bw = java.io.BufferedWriter(java.io.OutputStreamWriter(System.`out`))
	val q = br.readLine()!!.trim().toInt()
	var yutPos = Array(8) { -1 } 
	for(i in 1..q){
		var (y, v) = br.readLine()!!.trim().split(" ")
		var cnt = v.toCharArray().filter{ it == 'F' }.size
		if(cnt == 0) cnt = 5
		var num = when(y){
			"a" -> 0
			"b" -> 1
			"c" -> 2
			"d" -> 3
			"A" -> 4
			"B" -> 5
			"C" -> 6
			else -> 7
		}
		var prvPos = yutPos[num]
		var nxtPos = next(prvPos, cnt)
		yutPos[num] = nxtPos
		if(num < 4){
			for(j in 4..7){
				if(yutPos[j] == nxtPos){
					yutPos[j] = -1
				}
			}
			for(j in 0..3){
				if(prvPos >= 0 && yutPos[j] == prvPos){
					yutPos[j] = nxtPos
				}
			}
		}
		else{
			for(j in 0..3){
				if(yutPos[j] == nxtPos){
					yutPos[j] = -1
				}
			}
			for(j in 4..7){
				if(prvPos >= 0 && yutPos[j] == prvPos){
					yutPos[j] = nxtPos
				}
			}
		}
	}
	var realYutPan = yutPan.split("\n").map{ it.toCharArray() }
	for(i in 0..7){
		if(yutPos[i] == -1) continue
		var (x, y) = Position[yutPos[i]]
		if(i == 0) realYutPan[x][y] = 'a'
		if(i == 1) realYutPan[x][y+1] = 'b'
		if(i == 2) realYutPan[x+1][y] = 'c'
		if(i == 3) realYutPan[x+1][y+1] = 'd'
		if(i == 4) realYutPan[x][y] = 'A'
		if(i == 5) realYutPan[x][y+1] = 'B'
		if(i == 6) realYutPan[x+1][y] = 'C'
		if(i == 7) realYutPan[x+1][y+1] = 'D'
	}
	for(i in 0..31) bw.write(String(realYutPan[i]) + "\n")
	bw.flush()
	bw.close()
}


