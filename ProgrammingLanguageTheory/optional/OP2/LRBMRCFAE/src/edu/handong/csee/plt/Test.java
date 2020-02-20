package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.dfs.*;
import edu.handong.csee.plt.ast.store.MtSto;

public class Test {
	static Parser parser;
	static Interpreter interpreter;
	public static void main(String[] args) {
		parser = new Parser();
		interpreter = new Interpreter();
		
		// Test for Parser
		assertThat("{with {y 3} {with {z {fun {x} {+ x y}}} {with {y 10} {z 5}}}}", 
				"(app (fun y (app (fun z (app (fun y (app (id z) (num 5))) (num 10))) "
				+ "(fun x (add (id x) (id y))))) (num 3))", true, false);
		assertThat("{fun {x}{+ x 1}}", "(fun x (add (id x) (num 1)))", true, false);
		assertThat("{ {fun {x} {+ x 1}} 10}", "(app (fun x (add (id x) (num 1))) (num 10))", true, false);
		assertThat("{with {f {fun {x} x}} {f 10}}", "(app (fun f (app (id f) (num 10))) (fun x (id x)))", true, false);
		assertThat("{with {z {fun {x} {+ x y}}} {with {y 10} z}}"
				,"(app (fun z (app (fun y (id z)) (num 10))) (fun x (add (id x) (id y))))",true,false);
		assertThat("{- 5 {+ 1 2 3}}", "Bad Syntax: {+ 1 2 3} Expression Size: 4", true, true);
		assertThat("{rec {fac {fun {n} {if0 n 1 {* n {fac {- n 1}}}}}} {fac 10}}",
				"(rec fac (fun n (if0 (id n) (num 1) (mult (id n) (app (id fac) (sub (id n) (num 1))))))" + 
				" (app (id fac) (num 10)))",true,false);
		assertThat("{with {b {newbox 0}} {seqn {setbox b {+ 1 {openbox b}}} {openbox b}}}","(app (fun b (seqn (setbox (id b) (add (num 1) (openbox (id b)))) (openbox (id b)))) (newbox (num 0)))",true,false);
		assertThat("{with {b {newbox 7}} {seqn {setbox b 10} {openbox b}}}","(app (fun b (seqn (setbox (id b) (num 10)) (openbox (id b)))) (newbox (num 7)))",true,false);
		assertThat("{with {b {newbox 7}} {{fun {box} {seqn {setbox box 10} {+ 10 {openbox b}}}} b}}","(app (fun b (app (fun box (seqn (setbox (id box) (num 10)) (add (num 10) (openbox (id b))))) (id b))) (newbox (num 7)))",true,false);
		assertThat("{with {swap {refun {x} {refun {y} {with {z x} {seqn {setvar x y} {setvar y z}}}}}} {with {a 10} {with {b 20} {seqn {{swap a} b} b}}}}"
				, "(app (fun swap (app (fun a (app (fun b (seqn (app (app (id swap) (id a)) (id b)) (id b))) (num 20))) (num 10))) (refun x (refun y (app (fun z (seqn (setvar x (id y)) (setvar y (id z)))) (id x)))))", true, false);
		assertThat("{with {swap {fun {x}{fun {y}{with {z x}{seqn {setvar x y}{setvar y z}}}}}} {with {a 10}{with {b 20}{seqn {{swap a} b} b}}}}"
				, "(app (fun swap (app (fun a (app (fun b (seqn (app (app (id swap) (id a)) (id b)) (id b))) (num 20))) (num 10))) (fun x (fun y (app (fun z (seqn (setvar x (id y)) (setvar y (id z)))) (id x)))))",true,false);
		
		// Test for Interpreter
		assertThat("{with {x 3} {with {f {fun {y} {+ x y}}} {with {x 5} {f 4}}}}"
				, "(v*s (numV 7) (aSto 4 (numV 4) (aSto 3 (numV 5) (aSto 2 (closureV y (add (id x) (id y)) (aSub y 2 (aSub x 1 (aSub x 1 (mtSub))))) (aSto 1 (numV 3) (mtSto))))))",false, false);
		assertThat("{with {y 3}{with {z {fun {x} {+ x y}}} {with {y 10} z}}}"
				, "(v*s (closureV x (add (id x) (id y)) (aSub x 2 (aSub y 1 (aSub y 1 (mtSub))))) (aSto 3 (numV 10) (aSto 2 (closureV x (add (id x) (id y)) (aSub x 2 (aSub y 1 (aSub y 1 (mtSub))))) (aSto 1 (numV 3) (mtSto)))))",false, false);
		assertThat("{with {z {fun {x} {+ x y}}} {with {y 10} z}}", 
				"(v*s (closureV x (add (id x) (id y)) (aSub x 1 (mtSub))) (aSto 2 (numV 10) (aSto 1 (closureV x (add (id x) (id y)) (aSub x 1 (mtSub))) (mtSto))))",false, false);
		assertThat("{with {z {fun {x} {+ x y}}} {with {y 10}{z 5}}}"
				, "Free Identifier: y",false, true);
		assertThat("{with {f {fun {x} x}} {f 10}}"
				, "(v*s (numV 10) (aSto 2 (numV 10) (aSto 1 (closureV x (id x) (aSub x 1 (mtSub))) (mtSto))))",false, false);
		
		// recursion test case
		assertThat("{rec {fac {fun {n} {if0 n 1 {* n {fac {- n 1}}}}}} {fac 10}}", 
				"(v*s (numV 3628800) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 0)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 1)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 2)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 3)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 4)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 5)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 6)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 7)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 8)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub fac 1 (mtSub))) (numV 9)) (aSto 2 (numV 10) (aRecSto 1 (closureV n (if0 (id n) (num 1) (mult (id n) (app (id fac) (sub (id n) (num 1))))) (aSub n 2 (aSub fac 1 (mtSub)))) (mtSto))))))))))))))",false,false);
		assertThat("{rec {sum {fun {n} {if0 n 0 {+ n {sum {- n 1}}}}}} {sum 10}}"
				,"(v*s (numV 55) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 0)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 1)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 2)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 3)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 4)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 5)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 6)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 7)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 8)) (aSto 2 (exprV (sub (id n) (num 1)) (aSub n 2 (aSub sum 1 (mtSub))) (numV 9)) (aSto 2 (numV 10) (aRecSto 1 (closureV n (if0 (id n) (num 0) (add (id n) (app (id sum) (sub (id n) (num 1))))) (aSub n 2 (aSub sum 1 (mtSub)))) (mtSto))))))))))))))",false,false);
		
		// fibonacci function makes infinite loop
//		assertThat("{rec {fibo {fun {n} {if0 {- n 1} 1 {if0 {- n 2} 1 {+ {fibo {- n 1}} {fibo {- n 2}}}}}}} {fibo 3}}"
//				,"(v*s (numV 55) (aSto 110 (numV 2) (aSto 109 (numV 1) (aSto 108 (numV 2) (aSto 107 (numV 3) (aSto 106 (numV 4) (aSto 105 (numV 1) (aSto 104 (numV 2) (aSto 103 (numV 3) (aSto 102 (numV 2) (aSto 101 (numV 1) (aSto 100 (numV 2) (aSto 99 (numV 3) (aSto 98 (numV 4) (aSto 97 (numV 5) (aSto 96 (numV 6) (aSto 95 (numV 1) (aSto 94 (numV 2) (aSto 93 (numV 3) (aSto 92 (numV 2) (aSto 91 (numV 1) (aSto 90 (numV 2) (aSto 89 (numV 3) (aSto 88 (numV 4) (aSto 87 (numV 5) (aSto 86 (numV 2) (aSto 85 (numV 1) (aSto 84 (numV 2) (aSto 83 (numV 3) (aSto 82 (numV 4) (aSto 81 (numV 1) (aSto 80 (numV 2) (aSto 79 (numV 3) (aSto 78 (numV 2) (aSto 77 (numV 1) (aSto 76 (numV 2) (aSto 75 (numV 3) (aSto 74 (numV 4) (aSto 73 (numV 5) (aSto 72 (numV 6) (aSto 71 (numV 7) (aSto 70 (numV 8) (aSto 69 (numV 1) (aSto 68 (numV 2) (aSto 67 (numV 3) (aSto 66 (numV 2) (aSto 65 (numV 1) (aSto 64 (numV 2) (aSto 63 (numV 3) (aSto 62 (numV 4) (aSto 61 (numV 5) (aSto 60 (numV 2) (aSto 59 (numV 1) (aSto 58 (numV 2) (aSto 57 (numV 3) (aSto 56 (numV 4) (aSto 55 (numV 1) (aSto 54 (numV 2) (aSto 53 (numV 3) (aSto 52 (numV 2) (aSto 51 (numV 1) (aSto 50 (numV 2) (aSto 49 (numV 3) (aSto 48 (numV 4) (aSto 47 (numV 5) (aSto 46 (numV 6) (aSto 45 (numV 7) (aSto 44 (numV 2) (aSto 43 (numV 1) (aSto 42 (numV 2) (aSto 41 (numV 3) (aSto 40 (numV 4) (aSto 39 (numV 1) (aSto 38 (numV 2) (aSto 37 (numV 3) (aSto 36 (numV 2) (aSto 35 (numV 1) (aSto 34 (numV 2) (aSto 33 (numV 3) (aSto 32 (numV 4) (aSto 31 (numV 5) (aSto 30 (numV 6) (aSto 29 (numV 1) (aSto 28 (numV 2) (aSto 27 (numV 3) (aSto 26 (numV 2) (aSto 25 (numV 1) (aSto 24 (numV 2) (aSto 23 (numV 3) (aSto 22 (numV 4) (aSto 21 (numV 5) (aSto 20 (numV 2) (aSto 19 (numV 1) (aSto 18 (numV 2) (aSto 17 (numV 3) (aSto 16 (numV 4) (aSto 15 (numV 1) (aSto 14 (numV 2) (aSto 13 (numV 3) (aSto 12 (numV 2) (aSto 11 (numV 1) (aSto 10 (numV 2) (aSto 9 (numV 3) (aSto 8 (numV 4) (aSto 7 (numV 5) (aSto 6 (numV 6) (aSto 5 (numV 7) (aSto 4 (numV 8) (aSto 3 (numV 9) (aSto 2 (numV 10) (aRecSto 1 (closureV n (if0 (sub (id n) (num 1)) (num 1) (if0 (sub (id n) (num 2)) (num 1) (add (app (id fibo) (sub (id n) (num 1))) (app (id fibo) (sub (id n) (num 2)))))) (aSub fibo 1 (mtSub))) (mtSto))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))",false,false);
		
		// variable test case
		assertThat("{with {b {newbox 0}} {seqn {setbox b {+ 1 {openbox b}}} {openbox b}}}"
				,"(v*s (numV 1) (aSto 1 (numV 1) (aSto 2 (boxV 1) (aSto 1 (numV 0) (mtSto)))))",false,false);
		assertThat("{with {b {newbox 7}} {seqn {setbox b 10} {openbox b}}}"
				,"(v*s (numV 10) (aSto 1 (numV 10) (aSto 2 (boxV 1) (aSto 1 (numV 7) (mtSto)))))",false,false);
		assertThat("{with {b {newbox 7}} {{fun {box} {seqn {setbox box 10} {+ 10 {openbox b}}}} b}}"
				,"(v*s (numV 20) (aSto 1 (numV 10) (aSto 3 (boxV 1) (aSto 2 (boxV 1) (aSto 1 (numV 7) (mtSto))))))",false,false);
		assertThat("{with {swap {refun {x} {refun {y} {with {z x} {seqn {setvar x y} {setvar y z}}}}}} {with {a 10} {with {b 20} {seqn {{swap a} b} b}}}}"
				, "(v*s (numV 10) (aSto 3 (numV 10) (aSto 2 (numV 20) (aSto 4 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 1 (refclosV x (refun y (app (fun z (seqn (setvar x (id y)) (setvar y (id z)))) (id x))) (mtSub)) (mtSto))))))))", false, false);
		assertThat("{with {swap {fun {x} {fun {y} {with {z x} {seqn {setvar x y} {setvar y z}}}}}} {with {a 10} {with {b 20} {seqn {{swap a} b} b}}}}"
				, "(v*s (numV 20) (aSto 5 (numV 10) (aSto 4 (numV 20) (aSto 6 (numV 10) (aSto 5 (numV 20) (aSto 4 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 1 (closureV x (fun y (app (fun z (seqn (setvar x (id y)) (setvar y (id z)))) (id x))) (aSub x 1 (mtSub))) (mtSto))))))))))",false,false);
		
		// laziness test case
		assertThat("{{fun {x} 0} {+ 1 {fun {y} 2}}}"
				,"(v*s (numV 0) (aSto 1 (exprV (add (num 1) (fun y (num 2))) (aSub x 1 (mtSub)) (dummyV)) (mtSto)))",false,false);
		assertThat("{with {y 3}{with {z {fun {x} {+ x y}}} {with {y 10} z}}}"
				,"(v*s (closureV x (add (id x) (id y)) (aSub x 2 (aSub y 1 (aSub y 1 (mtSub))))) (aSto 3 (numV 10) (aSto 2 (closureV x (add (id x) (id y)) (aSub x 2 (aSub y 1 (aSub y 1 (mtSub))))) (aSto 1 (numV 3) (mtSto)))))",false,false);
		assertThat("{{fun {x} x} {+ 1 {fun {y} 2}}}"
				,"class edu.handong.csee.plt.ast.value.ClosureV cannot be cast to class edu.handong.csee.plt.ast.value.NumV (edu.handong.csee.plt.ast.value.ClosureV and edu.handong.csee.plt.ast.value.NumV are in unnamed module of loader 'app')",false,true);
	}
	
	private static void assertThat(String str1, String str2, boolean isParser, boolean isExcept) {
		try {			
			if(isParser) {			
				str1 =  parser.parse(str1).getASTCode();
			}else {
				str1 =  interpreter.interp(parser.parse(str1), new MtSub(), new MtSto()).getASTCode();
			}
		}catch(RuntimeException e) {
			if(isExcept) {
				str1 = e.getMessage();
			}else {
				throw e;
			}
		}
		
		if(str1.equals(str2)) {
			System.out.println("True");
		}else{
			String err = String.format("result:%s is not matched with expected: %s", str1, str2);
			throw new RuntimeException(err);
		}
	}
}
