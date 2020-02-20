package edu.handong.csee.plt.ast.rbmrcfae;

public class SetVar implements RBMRCFAE {
	private String id;
	private RBMRCFAE value;
	
	public SetVar(String id, RBMRCFAE value) {
		this.id = id;
		this.value = value;
	}
	
	public String getId() {
		return id;
	}
	
	public RBMRCFAE getValue() {
		return value;
	}
	
	@Override
	public String getASTCode() {
		return "(setvar "+ id +" "+ value.getASTCode() +")";
	}
}
