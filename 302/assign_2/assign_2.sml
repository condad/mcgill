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
