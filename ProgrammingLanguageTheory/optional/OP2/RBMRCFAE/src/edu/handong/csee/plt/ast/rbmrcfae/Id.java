package edu.handong.csee.plt.ast.rbmrcfae;

public class Id implements RBMRCFAE {
	String id;
	
	public Id(String id) {
		this.id = id;
	}
	
	public String getId() {
		return id;
	}
	
	@Override
	public String getASTCode() {
		return "(id " + id + ")";
	}
}
