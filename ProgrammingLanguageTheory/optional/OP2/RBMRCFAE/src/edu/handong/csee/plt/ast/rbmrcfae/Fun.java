package edu.handong.csee.plt.ast.rbmrcfae;

import edu.handong.csee.plt.ast.AST;

public class Fun implements RBMRCFAE {
	String param;
	AST body;
	
	public Fun(String param, AST body){
		this.param = param;
		this.body = body;
	}
	
	public String getParam() {
		return param;
	}
	
	public AST getBody() {
		return body;
	}
	
	@Override
	public String getASTCode() {
		return "(fun " + param + " " + body.getASTCode() + ")";
	}
}
