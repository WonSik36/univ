package edu.handong.csee.plt.ast.store;

import edu.handong.csee.plt.ast.value.Value;

public class ASto implements Store {
	private int adr;
	private Value v;
	private Store rest;
	
	public ASto(int adr, Value v, Store rest) {
		this.adr = adr;
		this.v = v;
		this.rest = rest;
	}
	
	public int getAdr() {
		return adr;
	}
	
	public Value getV() {
		return v;
	}
	
	public Store getRest() {
		return rest;
	}
	
	@Override
	public String getASTCode() {
		return "(aSto "+ adr +" "+v.getASTCode()+" "+ rest.getASTCode() +")";
	}

}
