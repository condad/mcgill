(*This funtion takes a three int date tuple and*)
(*returns a single int specifying the last day of the month*)

fun last_day (date: int*int*int): int = 
	case #2 date of
		1 => 31|
		2 => if (#1 date mod 400)=0 
			then 29 
			else if (#1 date mod 100)=0
				then 28
				else if (#1 date mod 4)=0
					then 29
					else 28|
		3 => 31|4 => 30|
		5 => 31|6 => 30|
		7 => 31|8 => 31|	
		9 => 30|10 => 31|
		11 => 30|12 => 31|
		 _ => let exception InvalidDate in
			raise InvalidDate end;

(* Takes a triple and returns whether of not said triple*)
(*is a valid date*)

fun valid_date (date: int*int*int): bool = 
	if (#1 date) > 0 then
		if (#3 date) > 0 then
			case #2 date of
				1 => (#3 date)<32|
				2 => if (#1 date mod 400)=0
                                		then (#3 date)<30
                                		else if (#1 date mod 100)=0
                                                	then (#3 date)<29
                                                	else if (#1 date mod 4)=0
                                                		then (#3 date)<30
                                                		else (#3 date)<29|
                       		3 => (#3 date)<32|4 => (#3 date)<31|
				5 => (#3 date)<32|6 => (#3 date)<31|
				7 => (#3 date)<32|8 => (#3 date)<32|
                       		9 => (#3 date)<31|10 => (#3 date)<31|
				11 => (#3 date)<31|12 => (#3 date)<32|
				 _ => false
		else false
			else false;

(*Takes a date triple and returns the next day*)

fun next_day (date: int*int*int): int*int*int = 
	if valid_date (#1 date, #2 date, #3 date) 
	then 
		if last_day (#1 date,#2 date,#3 date) = (#3 date) then
			case (#2 date) of
				12 => (#1 date+1, #2 date, 1)|
				_ => (#1 date, #2 date+1, 1)
		else 
			(#1 date, #2 date, #3 date +1)
		else let exception InvalidDate 
			in raise InvalidDate 
					end;

(*Takes two dates and returns true if the first comes*)
(*before the second. Returns false otherwise*)

fun precedes (date1: int*int*int, date2:int*int*int): bool = 
	if valid_date(date1) then
	if valid_date(date2) then
	
	if (#1 date1)<(#1 date2)
		then true
		else if (#2 date1)<(#2 date2)
			then true
			else if (#3 date1)<(#3 date2)
				then true
				else false
	else false
	else false;

(*Takes a list of dates and returns the earliest one*)

fun earliest_day (days: (int*int*int) list): int*int*int =
	case days of
		[] => let exception InvalidDate in
			 raise InvalidDate end|
		 x::xs => if null xs
				then x
				else 
					if precedes(x,hd(xs))
					then earliest_day(x::tl(xs))
					else earliest_day(hd(xs)::tl(xs));
(*This problem set deals with manipulating lists*)

fun unzip lst = let
	fun unzipper ([], l1, l2) = (l1, l2) |
	    unzipper ((a, b) :: r, l1, l2) 
			=unzipper(r, a::l1, b::l2)
	  in
	    unzipper (rev lst, [], []) end;

fun zip (l1, l2) =
	let
	  fun zipper ((x::xs),(y::ys),lst) = zipper (xs, ys, (x, y)::lst) |
			zipper (_, _, lst) = rev lst
	  in
	    		zipper (l1, l2, []) end;
(*These functions provide two different*)
(*implementations of the prefixsum list operation*)

fun incr (lst : int list, amt : int) : int list =
	case lst of
		[] => []|
		x :: xs => (x + amt) :: incr(xs, amt);

(*slower implementation used for proof via induction purposes*)

fun prefixSum (lst:int list):int list = 
	 case lst of
		[] => []|
		x::xs => x::incr (prefixSum xs, x);

(*faster linear implementation*)

fun prefixSumFast (lst: int list):int list =
	let
		fun psf [] sum  = rev sum|
			psf [x] sum = rev (x::sum)|
			psf (x :: y :: lst) sum = psf (y+x :: lst) (x :: sum)
		in
			psf lst [] end; 
