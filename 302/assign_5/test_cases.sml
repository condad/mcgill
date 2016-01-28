val ex1 = Let(Nat(5),("a",(Plus(Var("a"),Nat(2)))))
val ex2 = Plus(Var("a"),Nat(2))
val ex3 = Let(Var("y"),("x",Plus(Var("x"),Var("z"))))
val ex4 = Let(Nat(3),("z",(Let(Nat(2),("y",ex3)))))
val ex5 = Fun("fac","n",If(Eq(Var("n"),Nat(0)),Nat(1),
    Mult(Var("n"),(Apply(Var("fac"),(Mult(Var("n"),Nat(1))))))))
val ex6 = Fun("f","n",Plus(Nat(3),Var("n")))
val ex7 = Fun("g","n",If(Eq(Var("n"),Nat(0)),Nat(0), Plus(Nat(1),Apply(Var("g"),(Minus(Var("n"),Nat(1)))))))


(*
val cell0 = makeCell 0;
val test_cell_put5 = cell0 (Put(5));
val test_cell_put6 = cell0 (Put(6));
val test_cell_get = cell0 Get;
val test_cell_restore_first = cell0 Restore;
val test_cell_restore_second = cell0 Restore;
val test_cell_restore_third = cell0 Restore;
val test_cell_restore_fourth = cell0 Restore;
*)


