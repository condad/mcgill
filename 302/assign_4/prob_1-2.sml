(*Assignment 4 / COMP 302 / McGill University*)
(*Connor Sullivan, March 24/'15*)

datatype 'a rlist = Empty | Rcons of 'a * (('a rlist) ref)
datatype transactions = Withdraw of int | Deposit of int | Check_balance

fun insert (ck, x, lst_rf) =
	case !lst_rf of
		Empty => lst_rf := Rcons(x, ref Empty) |
		Rcons (a, r) => 
			if ck (x,a) then
				r := Rcons(x, r)
			else
				insert (ck, x, r)

fun make_protected_account (x,pwd) =
	let val balance = ref x in
		fn (trans, str) => if (str = pwd)
			then case trans of  
				Withdraw(a) => ((balance := !balance-a); !balance) |
				Deposit(a) => ((balance := !balance+a); !balance) |
				Check_balance => (!balance)
			else
				(print ("Wrong password.\n"); 0)
	end

