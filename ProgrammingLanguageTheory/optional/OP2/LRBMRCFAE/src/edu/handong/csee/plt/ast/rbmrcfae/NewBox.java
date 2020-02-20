package edu.handong.csee.plt.ast.rbmrcfae;

public class NewBox implements RBMRCFAE {
	private RBMRCFAE value;
	
	public NewBox(RBMRCFAE value) {
		this.value = value;
	}
	
	public RBMRCFAE getValue() {
		return value;
	}
	
	@Override
	public String getASTCode() {
		return "(newbox "+ value.getASTCode() +")";
	}

}
