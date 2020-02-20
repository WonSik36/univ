package edu.handong.csee.plt;

import java.util.ArrayList;
import edu.handong.csee.plt.ast.*;

public class Test {
	static Parser parser;
	static Interpreter interpreter;
	public static void main(String[] args) {
		parser = new Parser();
		interpreter = new Interpreter();
		
		// Test for Parser
		assertThat("{with {x 3} {with {f {fun {y} {+ x y}}} {with {x 5} {f 4}}}}", 
				"(with x (num 3) (with f (fun y (add (id x) (id y))) (with x (num 5) (app (id f) (num 4)))))", true, false);
		assertThat("{fun {x}{+ x 1}}", "(fun x (add (id x) (num 1)))", true, false);
		assertThat("{ {fun {x} {+ x 1}} 10}", "(app (fun x (add (id x) (num 1))) (num 10))", true, false);
		assertThat("{with {x 3} {with {f {fun {y} {+ x y}}} {with {x 5} {f 4}}}}", 
				"(with x (num 3) (with f (fun y (add (id x) (id y))) (with x (num 5) (app (id f) (num 4)))))", true, false);
		assertThat("{- 5 {+ 1 2 3}}", "Bad Syntax: {+ 1 2 3}", true, true);
		

		// Test for Interpreter
		assertThat("{with {x 3} {with {f {fun {y} {+ x y}}} {with {x 5} {f 4}}}}", "(num 7)",false, false);
		assertThat("{fun {a} {+ a a}}", "(fun a (add (id a) (id a)))",false, false);
		assertThat("{with {fn {fun {a} {+ a a}}} {with {x 1} {fn {with {y 10} {+ y x}}}}}", "(num 22)",false, false);
		assertThat("{with {x 3} {with {f {fun {y} {+ x y}}} {with {x 5} {f 4}}}}", "(num 7)",false, false);
		
		//dynamic scope issue
		assertThat("{with {y 3} {with {z {fun {x} {+ x y}}} {with {y 10} z}}}", 
				"(fun x (add (id x) (num 3)))",false, false);
		assertThat("{with {z {fun {x} {+ x y}}} {with {y 10} z}}", "(fun x (add (id x) (num 10)))",false, true);
		assertThat("{with {y 3} {with {z {fun {x} {+ x y}}} {with {y 10} {z 5}}}}", "(num 8)",false, true);
		assertThat("{with {z {fun {x} {+ x y}}} {with {y 10} {z 5}}}", "(num 15)",false, true);
	}
	
	private static void assertThat(String str1, String str2, boolean isParser, boolean isExcept) {
		try {			
			if(isParser) {		
				AST ast = parser.parse(str1);
				str1 =  ast.getASTCode();
			}else {
				str1 =  interpreter.interp(parser.parse(str1)).getASTCode();
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
