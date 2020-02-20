package edu.handong.csee.plt.ast.rbmrcfae;

import edu.handong.csee.plt.exception.BadMatchingException;

public class OpenBox implements RBMRCFAE {
	private RBMRCFAE id;
	
	public OpenBox(RBMRCFAE id) {
		if(!(id instanceof Id))
			throw new BadMatchingException("first parameter is not Id class");
		this.id = id;
	}
	
	public RBMRCFAE getId() {
		return id;
	}
	
	@Override
	public String getASTCode() {
		return "(openbox "+ id.getASTCode() +")";
	}
}
