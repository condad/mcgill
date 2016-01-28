		(* ASSIGNMENT 5 / COMP 302 / WINTER 2015 *)
(*Connor Sullivan, 260 421 531*)

	(*QUESTION 1*)

datatype exp = Nat of int | Bool of bool |Plus of exp * exp |
               Minus of exp * exp |Mult of exp * exp | If of exp * exp * exp |
               And of exp * exp | Not of exp | Eq of exp * exp |
               Var of string | Let of exp * (string * exp) |
               Fun of string * string * exp | Apply of exp * exp


fun remDuplicates [] = [] |
    remDuplicates (lst as x::xs) =
	let fun remove (x,[]) = [] |
		remove (x,lst as y::ys) =
			if x = y then remove(x,ys)
            		else y::remove(x,ys)
      	in x::remDuplicates(remove(x,xs)) end



fun free_list x = 		(*NOTE: I removed the hyphen from the name*)
	let fun free x lst = 	(*because it gave me an error*)
		case x of 
			Nat(a) => remDuplicates lst | Bool(a) => remDuplicates lst |
			Plus(a,b) => free a (free b lst) |
			Minus(a,b) => free a (free b lst) |
			Mult(a,b) => free a (free b lst) |
			If(a,b,c) => free a (free b (free c lst)) |
			And(a,b) => free a (free b lst) | Not(a) => free a lst | 
			Eq(a,b) => free a (free b lst) | Var(v) => lst @ [v] | 
			Let (a,(b,c)) => free a (List.filter (fn(z) => b <> z) (free c lst)) |
			Fun(a,b,c) => List.filter (fn(z) => b <> z andalso a <> z) (free c lst) |
			Apply(a,b) => free a (free b lst)
	in free x [] end


	(*QUESTION 2*)

datatype realSeq = Cons of real * (unit -> realSeq)

(*Part 1*)
fun catalan n =		(*uses foldl as specified*)
	let fun ctln 0 lst = Real.trunc ((**)List.foldl(**) (fn(a,b) => a*b) 1.00 lst) |
		ctln n lst = ctln (n-1) (((real (4*n-2)) / (real (n+1)))::lst)
	in ctln n [] end 

(*Part 2*)
fun tm x = (Real.fromInt (2*(2*x+1))) / (Real.fromInt (x+2)) 
fun force (Cons (a,s)) = s()
fun shd (Cons (x, _)) = x


fun helperSeq n = Cons(tm n, fn () => helperSeq (n+1))

val catalanSeq =	(*evaluates lazily*) 
	let 
		fun ctln x seq = Cons(x, fn () => ctln (x*(shd seq)) (force seq)) 
	in
		ctln 1.00 (helperSeq 0) end


	(*QUESTION 3*)

datatype 'a instr = Put of 'a | Get | Restore
exception None

fun makeCell x =
	let
		val now = ref [x]
	in
		fn (i) =>
			case i of
				Put(a) => ((now := [a]@(!now)); a) |
				Get => (case !now of x::xs => x) |
				Restore => (case !now of
					x::y::ys => ((now := y::ys); y) |
				_ => (print "Nothing to restore\n"; raise None))
	end







(*yeah baby*)
