package edu.handong.csee.plt.ast.rbmrcfae;

import edu.handong.csee.plt.exception.BadMatchingException;

public class SetBox implements RBMRCFAE {
	private RBMRCFAE id;
	private RBMRCFAE value;
	
	public SetBox(RBMRCFAE id, RBMRCFAE value) {
		if(!(id instanceof Id))
			throw new BadMatchingException("first parameter is not Id class");
		this.id = id;
		this.value = value;
	}
	
	public RBMRCFAE getId() {
		return id;
	}
	
	public RBMRCFAE getValue() {
		return value;
	}
	
	@Override
	public String getASTCode() {
		return "(setbox "+ id.getASTCode() +" "+ value.getASTCode() +")";
	}
}
