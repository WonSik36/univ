package edu.handong.csee.plt;

import java.util.ArrayList;
import edu.handong.csee.plt.ast.dfs.*;

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
		

		// Test for Interpreter
		assertThat("{with {x 3} {with {f {fun {y} {+ x y}}} {with {x 5} {f 4}}}}", "(numV 7)",false, false);
		assertThat("{with {y 3}{with {z {fun {x} {+ x y}}} {with {y 10} z}}}"
				, "(closureV x (add (id x) (id y)) (aSub y (numV 3) (mtSub)))",false, false);
		assertThat("{with {y 3}{with {z {fun {x} {+ x y}}} {with {y 10} z}}}", 
				"(closureV x (add (id x) (id y)) (aSub y (numV 3) (mtSub)))",false, false);
		assertThat("{with {z {fun {x} {+ x y}}} {with {y 10} z}}", 
				"(closureV x (add (id x) (id y)) (mtSub))",false, false);
		assertThat("{with {z {fun {x} {+ x y}}} {with {y 10}{z 5}}}"
				, "Free Identifier: y",false, true);
		assertThat("{with {f {fun {x} x}} {f 10}}", "(numV 10)",false, true);
		
		// recursion test case
		assertThat("{rec {fac {fun {n} {if0 n 1 {* n {fac {- n 1}}}}}} {fac 10}}", 
				"(numV 3628800)",false,false);
		assertThat("{rec {fibo {fun {n} {if0 {- n 1} 1 {if0 {- n 2} 1 {+ {fibo {- n 1}} {fibo {- n 2}}}}}}} {fibo 10}}"
				,"(numV 55)",false,false);
		assertThat("{rec {sum {fun {n} {if0 n 0 {+ n {sum {- n 1}}}}}} {sum 10}}"
				,"(numV 55)",false,false);
	}
	
	private static void assertThat(String str1, String str2, boolean isParser, boolean isExcept) {
		try {			
			if(isParser) {			
				str1 =  parser.parse(str1).getASTCode();
			}else {
				str1 =  interpreter.interp(parser.parse(str1), new MtSub()).getASTCode();
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
