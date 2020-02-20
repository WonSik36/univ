package edu.handong.csee.plt.ast.rcfae;

public class Id implements RCFAE {
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
