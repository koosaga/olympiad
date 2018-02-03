import java.util.*
import kotlin.math.abs

fun solve(ops : List<String>, v : Int){
    var err = false
    var nummode = false
    var l = Stack<Int>()
    l.push(v)
    for (s in ops){
        if(err) break
        if(nummode){
            l.add(s.toInt())
            nummode = false
        }
        if(s == "NUM"){
            nummode = true
        }
        if(s == "POP"){
            if(l.isEmpty()) err = true
            else l.pop()
        }
        if(s == "INV"){
            if(l.isEmpty()) err = true
            else{
                var x = -l.peek()
                l.pop()
                l.push(x);
            }
        }
        if(s == "DUP"){
            if(l.isEmpty()) err = true
            else l.push(l.peek())
        }
        if(s == "SWP"){
            if(l.size < 2) err = true
            else{
                var x = l.pop()
                var y = l.pop()
                l.push(x)
                l.push(y)
            }
        }
        if(s == "ADD"){
            if(l.size < 2) err = true
            else{
                var x = l.pop()
                var y = l.pop()
                if(abs(x + y) > 1000000000) err = true
                else l.push(x + y)
            }
        }
        if(s == "SUB"){
            if(l.size < 2) err = true
            else{
                var x = l.pop()
                var y = l.pop()
                if(abs(y - x) > 1000000000) err = true
                else l.push(y - x)
            }
        }
        if(s == "MUL"){
            if(l.size < 2) err = true
            else{
                var x = l.pop().toLong()
                var y = l.pop().toLong()
                if(abs(y * x) > 1000000000) err = true
                else l.push((y * x).toInt())
            }
        }
        if(s == "DIV"){
            if(l.size < 2) err = true
            else{
                var x = l.pop()
                var y = l.pop()
                if(x == 0) err = true;
                else {
                    var t = abs(y) / abs(x)
                    if ((x < 0) != (y < 0)) t = -t
                    l.push(t)
                }
            }
        }
        if(s == "MOD"){
            if(l.size < 2) err = true
            else{
                var x = l.pop()
                var y = l.pop()
                if(x == 0) err = true
                else {
                    var t = abs(y) % abs(x)
                    if (y < 0) t = -t
                    l.push(t)
                }
            }
        }
    }
    if(err || l.size != 1) println("ERROR")
    else println(l.peek())
}

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
    while(true){
        var s = next()
        if(s == "QUIT") break
        var l = mutableListOf<String>()
        while(true){
            if(s == "END") break
            l.add(s)
            s = next()
            if(s == "END") break
        }
        var tc = nextInt()
        for (i in 1..tc){
            solve(l, nextInt())
        }
        println()
    }
}
