datatype 'a tree =
	Empty |
	Node of (int*'a)*'a tree*'a tree

fun collect p t =
	case t of 
		Empty => [] |
		Node ((a,b),l,r) =>
			let exception Found of (int*string) list
			in
				(if p a then raise Found [(a, b)]		
					else collect p l @ collect p r)
				handle Found entry => collect p l @ [(a,b)] @ collect p r
			end

fun gather f Empty cont = cont ([]) |
	gather f (Node((a,b), l, r)) cont = 
    		if f a then
			gather f l (fn left_child => left_child@[(a,b)]@(gather f r cont))
    		else
			gather f l (fn left_child => left_child@(gather f r cont))

datatype 'a church = C of ('a -> 'a) * 'a  -> 'a

fun create 0 = C (fn (f,x) => x)
  | create n = 
  	let val C c = create (n-1) 
  	in C (fn (f,x) => f (c (f,x)))
 	end

fun churchToInt (C c) =  (c (fn x=> x+1, 0))

fun SUCC (C c) =  C (fn (f,x) => c (f,x))
