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
