package edu.handong.csee.plt;

import java.util.ArrayList;

import edu.handong.csee.plt.ast.*;

public class Parser {

	public AST parse(String exampleCode) {
		exampleCode = desugar(exampleCode);
		ArrayList<String> subExpressions = splitExpressionAsSubExpressions(exampleCode);
		
		if(subExpressions.size() > 3) {
			String err = String.format("Bad Syntax: %s", exampleCode);
			throw new RuntimeException(err);
		}
		
		
		// num
		if(subExpressions.size() == 1 && isNumeric(subExpressions.get(0))) {

			return new Num(subExpressions.get(0));
		}

		// add
		if(subExpressions.get(0).equals("+")) {
			
			return new Add(parse(subExpressions.get(1)),parse(subExpressions.get(2)));
		}
		
		// sub
		if(subExpressions.get(0).equals("-")) {
			
			return new Sub(parse(subExpressions.get(1)),parse(subExpressions.get(2)));
		}
		
		// with
		if(subExpressions.get(0).equals("with")) {
			ArrayList<String> list = splitExpressionAsSubExpressions(subExpressions.get(1));
			return new With(list.get(0),parse(list.get(1)),parse(subExpressions.get(2)));
		}
		
		// id
		if(subExpressions.size() == 1) {
			
			return new Id(subExpressions.get(0));
		}
		
		// fun
		if(subExpressions.get(0).equals("fun")) {
			String param = splitExpressionAsSubExpressions(subExpressions.get(1)).get(0);
			return new Fun(param, parse(subExpressions.get(2)));
		}
				
		// app
		if(subExpressions.size() == 2) {
			
			return new App(parse(subExpressions.get(0)),parse(subExpressions.get(1)));
		}		
		
		String err = String.format("Bad Syntax: %s", exampleCode);
		throw new RuntimeException(err);
	}
	
	public String desugar(String code) {
		StringBuffer sb = new StringBuffer();
		sb.append(code.charAt(0));
		for(int i=1;i<code.length();i++) {
			if(code.charAt(i) == '{' && code.charAt(i-1) != ' ') {
				sb.append(" ");
			}
			sb.append(code.charAt(i));
		}
		
		return sb.toString();
	}

	public ArrayList<String> splitExpressionAsSubExpressions(String exampleCode) {

		// deal with brackets first.
		if((exampleCode.startsWith("{") && !exampleCode.endsWith("}"))
				|| (!exampleCode.startsWith("{") && exampleCode.endsWith("}"))) {
			System.out.println("Syntax error");
			System.exit(0);
		}

		// cut brackets
		if(exampleCode.startsWith("{"))
			exampleCode = exampleCode.substring(1, exampleCode.length()-1);


		return getSubExpressions(exampleCode);
	}



	/**
	 * This method return a list of sub-expression from the given expression.
	 * For example, {+ 3 {+ 3 4}}  -> +, 2, {+ 3 4}
	 * TODO JC was sleepy while implementing this method...it has complex logic and might be buggy...
	 * You can do better or find an external library.
	 * @param exampleCode
	 * @return list of sub expressions 
	 */
	public ArrayList<String> getSubExpressions(String exampleCode) {

		ArrayList<String> sexpressions = new ArrayList<String>();
		int openingParenthesisCount = 0;
		String strBuffer = "";
		for(int i=0; i < exampleCode.length()  ;i++) {
			if(i==0 || (i==0 && exampleCode.charAt(i) == '{')) {
				strBuffer = strBuffer + exampleCode.charAt(i);
				continue;
			} else if(exampleCode.charAt(i)==' ' && openingParenthesisCount==0){
				// buffer is ready to be a subexpression
				if(!strBuffer.isEmpty()) {
					sexpressions.add(strBuffer);
					strBuffer = ""; // Ready to start a new buffer
				}
				continue;
			} else {
				if(exampleCode.charAt(i)=='{' && openingParenthesisCount==0){
					openingParenthesisCount++;
					// Ready to start a new buffer
					strBuffer = "" + exampleCode.charAt(i);
					continue;
				} else if(exampleCode.charAt(i)=='{') {
					openingParenthesisCount++;
					strBuffer = strBuffer + exampleCode.charAt(i);
					continue;
				} else if(exampleCode.charAt(i)=='}' && openingParenthesisCount>0) {
					openingParenthesisCount--;
					strBuffer = strBuffer + exampleCode.charAt(i);
					continue;
				} else if(exampleCode.charAt(i)=='}') {
					// buffer is ready to be a subexpression
					sexpressions.add(strBuffer);
					continue;
				}
			}
			strBuffer = strBuffer + exampleCode.charAt(i);
		}
		
		sexpressions.add(strBuffer);

		return sexpressions;
	}

	public static boolean isNumeric(String str)
	{
		return str.matches("-?\\d+(\\.\\d+)?");  //match a number with optional '-' and decimal.
	}

}
