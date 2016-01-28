(*Take a list and returns a list sans duplicates*)

fun remDuplicates [] = []	|
	remDuplicates (lst as x::xs) =
		let fun remove (x,[]) = []	|
				remove (x,lst as y::ys) =
			if x = y
                then remove(x,ys)
            else y::remove(x,ys)
      	in
        	x::remDuplicates(remove(x,xs))
    	end

val poly:(real->real) =
	fn x:real => x*x - x - 6.00

val linearfunc: (real->real) = 
		fn x:real => 2.00 * x
	

(*Take a function and a guess and returns the root*)
(*via Newton's method*)

fun newton (funk:(real->real),guess:real,e:real) =
	let fun derivative x =
				(funk (x + e) - funk (x - e)) / (2.0 * e)
		fun nwt x =
					x - (funk x)/(derivative x)
		fun check x i e =
				if abs (funk x) < e
					then x
				else if (i < 1000)
					then 
						check (nwt x) (i+1) e 
					else let 
							exception Diverge
						in 
							raise Diverge end
		in
			check guess 0 e
		end

val root = newton (poly, ~30.00, 0.0000001);

fun sum (f:real->real, a:real, b:real, inc:real->real) =
    	if (a > b) then 0.00
    	else 
    		(f a) + sum (f, inc(a), b, inc)

(*This function integrates the product of two given functions*)
(*f and g, taking dy as the differential. This function uses the sum *)
(*function defined above from the lectures as an auxillary*)

fun h (f:real->real, g:real->real, dy:real) = fn x =>
			dy * sum(fn n => (f n)*(g (x+n)), 0.00, x,fn i => (i+dy))

val integral = h (poly, linearfunc, 0.0001);

val test:real = (integral 35.00);

Control.Print.printDepth := 100;

datatype Mathexp =
      Num of int
    | Var of string
    | Neg of Mathexp
    | Add of Mathexp * Mathexp
    | Mul of Mathexp * Mathexp

fun simplify (express : Mathexp) : Mathexp =
case express of
      Neg exp =>        let val e = simplify exp
                        in
                           case e of
                                 Num 0 => Num 0 (* Special case of e = 0*)
                               | _ => Neg e (* Negative*)
                        end
    | Add (exp1, exp2) => let
                            val a = simplify exp1
                            val b = simplify exp2
                        in
                            case (a, b) of (* Handle the identity 0 + x = x and vice versa *)
                                  (Num 0, b) => b
                                | (a, Num 0) => a
                                | (_, _) => Add (a, b) (*trivial*) 
                        end
    | Mul (exp1, exp2) => let
                            val a = simplify exp1
                            val b = simplify exp2
                        in
                            case (a, b) of
                                  (Num 0, b) => Num 0 (* Handle the identity 0 * x = 0 and vice versa *)
                                | (a, Num 0) => Num 0
                                | (a, Num 1) => a
                                | (Num 1, b) => b (* Handle the identity 1 * x = x and vice versa *)
                                | (_, _) => Mul (a, b) (*trivial*) 
                        end
    | _ => express 
    
fun diff (express : Mathexp, x : string) : Mathexp =
	let
    	fun diff_helper (express : Mathexp, x : string) : Mathexp =
    	case express of
        	Var s => if s = x then Num 1 else Var s (* dy/dy {x} *) 
        	| Neg exp => Neg (diff_helper (exp, x)) (* Differentiate the inside then make it negative again *)
        	| Mul (exp1, exp2) => let (* f'(x)g(x) + f(x)g'(x) *)
                                		val left = Mul (diff_helper (exp1, x), exp2)
                                		val right = Mul (exp1, diff_helper(exp2, x))
                            		in Add (left, right) end
        | Add (exp1, exp2) => Add (diff_helper (exp1, x), diff_helper (exp2, x)) 
        | Num i => Num 0 (* Trivial derivative of 0 *) 
in
    simplify (diff_helper (express, x))
end
