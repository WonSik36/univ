package edu.handong.csee.plt.ast.rbmrcfae;

public class Fun implements RBMRCFAE {
	String param;
	RBMRCFAE body;
	
	public Fun(String param, RBMRCFAE body){
		this.param = param;
		this.body = body;
	}
	
	public String getParam() {
		return param;
	}
	
	public RBMRCFAE getBody() {
		return body;
	}
	
	@Override
	public String getASTCode() {
		return "(fun " + param + " " + body.getASTCode() + ")";
	}
}
