package edu.handong.csee.plt.ast.store;

import edu.handong.csee.plt.ast.value.Value;

public class ARecSto implements Store {
	private int adr;
	private Value valueBox;
	private Store rest;
	
	public ARecSto(int adr, Value valueBox, Store rest) {
		this.adr = adr;
		this.valueBox = valueBox;
		this.rest = rest;
	}
	
	public int getAdr() {
		return adr;
	}
	
	public Value getValueBox() {
		return valueBox;
	}
	
	public void setValueBox(Value valueBox) {
		this.valueBox = valueBox;
	}
	
	public Store getRest() {
		return rest;
	}
	
	@Override
	public String getASTCode() {
		return "(aRecSto " + adr + " " + valueBox.getASTCode() + " " + rest.getASTCode() + ")";
	}
}
