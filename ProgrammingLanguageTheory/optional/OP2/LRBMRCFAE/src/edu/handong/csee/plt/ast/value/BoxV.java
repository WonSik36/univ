package edu.handong.csee.plt.ast.value;

public class BoxV implements Value {
	private int adr;
	
	public BoxV(int adr) {
		this.adr = adr;
	}
	
	public int getAdr() {
		return adr;
	}
	
	@Override
	public String getASTCode() {
		return "(boxV "+ adr + ")";
	}

}
