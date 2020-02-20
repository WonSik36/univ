package edu.handong.csee.plt.ast.rbmrcfae;

public class ReFun implements RBMRCFAE {
	private String param;
	private RBMRCFAE body;
	
	public ReFun(String param, RBMRCFAE body){
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
		return "(refun " + param + " " + body.getASTCode() + ")";
	}
}
