/*
	how to execute the program

	cd C:\Users\wonsik\"OneDrive - handong.edu"\ univ\2019_2\ProgrammingLanguageTheory\hw\optional\OP2\FAE\src

	1. cd [your path]\FAE\src  
	2. javac .\edu\handong\csee\plt\*.java .\edu\handong\csee\plt\ast\*.java .\edu\handong\csee\plt\astvalue\*.java .\edu\handong\csee\plt\dfs\*.java
	3. java edu.handong.csee.plt.Main
*/

package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.*;
import edu.handong.csee.plt.dfs.MtSub;

public class Main {
	
	static boolean onlyParser = false; // for -p option
	
	public static void main(String[] args) {
		if(args.length == 0) {
			System.out.println("There is no expression");
			return;
		}
			
		String targetCode;
		
		if(args[0].equals("-p")) {			
			onlyParser = true;
			targetCode = args[1];
		}else {
			targetCode = args[0];
		}
		
		try {
			// Parser
			Parser parser = new Parser();
			AST ast = parser.parse(targetCode);
			
			if(ast == null)
				System.out.println("Syntax Error!");
			
			if(onlyParser) {
				System.out.println(ast.getASTCode());
			}else {
				Interpreter interpreter = new Interpreter();	
				String result = interpreter.interp(ast, new MtSub()).getASTValueCode();
				
				System.out.println(result);
			}			
		}catch(RuntimeException e) {
			System.out.println(e.getMessage());
		}
	}
}
