package edu.handong.csee.plt.dfs;

import edu.handong.csee.plt.astvalue.*;

public class DefrdSub {
	
	public static void main(String[] args) {
		//(aSub 'y (numV 3) (mtSub)))
		DefrdSub ds = new ASub("y",new NumV("3"), new MtSub());
		System.out.println(ds.getDSCode());
	}
	
	public String getDSCode() {
		String dsCode="";
		if(this instanceof ASub)
			dsCode = ((ASub)this).getDSCode();
		
		if(this instanceof MtSub)
			dsCode = ((MtSub)this).getDSCode();
		

		return dsCode;
	}
}
