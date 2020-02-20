package edu.handong.csee.plt;

public class Test {
	static Parser parser;
	static Interpreter interpreter;
	public static void main(String[] args) {
		parser = new Parser();
		interpreter = new Interpreter();

		// Test for Parser
		assertThat("{+ 1 2}", "(add (num 1) (num 2))", true, false);
		assertThat("{with {x 5} {+ 8 2}}", "(with x (num 5) (add (num 8) (num 2)))", true, false);
		assertThat("{with {x 5} {+ x x}}", "(with x (num 5) (add (id x) (id x)))", true, false);
		assertThat("{- 5 {+ 1 2 3}}", "Bad Syntax: {+ 1 2 3}", true, true);

		// Test for Interpreter
		assertThat("{+ {- 3 4} 7}", "6",false, false);
		assertThat("{with {x 5} {+ 8 2}}", "10",false, false);
		assertThat("{with {x 5} {+ x x}}", "10",false, false);
		assertThat("{with {x {+ 5 5}} {with {y {- x 3}} {+ y y}}}", "14",false, false);
		assertThat("{with {x 5} {+ x {with {y x} y}}}", "10",false, false);
		assertThat("{with {x {+ 5 5}} {with {y {- x 3}} {+ y z}}}", "Free identifier",false, true);
	}
	
	private static void assertThat(String str1, String str2, boolean isParser, boolean isExcept) {
		try {			
			if(isParser) {			
				str1 =  parser.parse(str1).getASTCode();
			}else {
				str1 =  interpreter.interp(parser.parse(str1));
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
