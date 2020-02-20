package edu.handong.csee.plt;

import java.util.ArrayList;
import java.util.List;

import edu.handong.csee.plt.ast.dfs.*;
import edu.handong.csee.plt.ast.rbmrcfae.*;
import edu.handong.csee.plt.ast.store.*;
import edu.handong.csee.plt.ast.value.*;
import edu.handong.csee.plt.ast.vs.*;
import edu.handong.csee.plt.exception.FreeAdressException;
import edu.handong.csee.plt.exception.FreeIdentifierException;
import edu.handong.csee.plt.exception.UndefinedASTException;

public class Interpreter {
	List<String> exprList = new ArrayList<>();
	
	public Interpreter() {
		String[] list = {"Add","Sub","Mult"};
		
		for(String str : list) {			
			exprList.add(str);
		}
	}
	
	public ValueStore interp(RBMRCFAE ast, Dfs ds, Store st) {
		
		if(ast instanceof Num) {
			Num num = (Num)ast; 
			return new VS(new NumV(num.getStrNum()),st);
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			VS vs1 = (VS)interp(add.getLhs(),ds,st);
			VS vs2 = (VS)interp(add.getRhs(),ds,vs1.getSt());
			
			NumV numV1 = (NumV)strict(vs1.getValue());
			NumV numV2 = (NumV)strict(vs2.getValue());
			
			int res = Integer.parseInt(numV1.getStrNum()) 
					+ Integer.parseInt(numV2.getStrNum());
			VS ret = new VS(new NumV(Integer.toString(res)),vs2.getSt());
			
			return ret;
		}
		
		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			VS vs1 = (VS)interp(sub.getLhs(),ds,st);
			VS vs2 = (VS)interp(sub.getRhs(),ds,vs1.getSt());
			
			NumV numV1 = (NumV)strict(vs1.getValue());
			NumV numV2 = (NumV)strict(vs2.getValue());
			
			int res = Integer.parseInt(numV1.getStrNum()) 
					- Integer.parseInt(numV2.getStrNum());
			VS ret = new VS(new NumV(Integer.toString(res)),vs2.getSt());
			
			return ret;
		}
		
		if(ast instanceof Mult) {
			Mult mult = (Mult)ast;
			VS vs1 = (VS)interp(mult.getLhs(),ds,st);
			VS vs2 = (VS)interp(mult.getRhs(),ds,vs1.getSt());
			
			NumV numV1 = (NumV)strict(vs1.getValue());
			NumV numV2 = (NumV)strict(vs2.getValue());
			
			int res = Integer.parseInt(numV1.getStrNum()) 
					* Integer.parseInt(numV2.getStrNum());
			VS ret = new VS(new NumV(Integer.toString(res)),vs2.getSt());
			
			return ret;
		}
		
		if(ast instanceof Id) {
			Id id = (Id)ast;
			return new VS(strict(storeLookup(lookup(id.getId(),ds),st)), st);				
		}
		
		if(ast instanceof Fun) {
			Fun fun = (Fun)ast;
			int newAdr = malloc(st);
			ASub aSub = new ASub(fun.getParam(),newAdr,ds);
			return new VS(new ClosureV(fun.getParam(), fun.getBody(), aSub),st);
		}
		
		if(ast instanceof ReFun) {
			ReFun refun = (ReFun)ast;
			return new VS(new RefClosV(refun.getParam(), refun.getBody(), ds),st);
		}
		
		if(ast instanceof App) {
			App app = (App)ast;
			VS vs1 = (VS)interp(app.getFtn(),ds,st);
			Value fValue = strict(vs1.getValue());
			Store fStore = vs1.getSt();
			
			if(fValue instanceof ClosureV) {
				ClosureV cv = (ClosureV)fValue;
				String cParam = cv.getParam();
				RBMRCFAE cBody = (RBMRCFAE)cv.getBody();
				Dfs cDs = cv.getDS();
				
				String className = app.getArg().getClass().getSimpleName();
				// apply exprV
				if(exprList.contains(className)) {
					ExprV exprV = new ExprV(app.getArg(),cDs,fStore,new DummyV());
					int paramAdr = lookup(cParam,cDs);
					
					return interp(cBody,cDs, new ASto(paramAdr,exprV,fStore));

				}else {
					VS vs2 = (VS)interp(app.getArg(),ds,fStore);
					int newAdr = malloc(vs2.getSt());
					Value aValue = vs2.getValue();
					Store aStore = vs2.getSt();
					
					return interp(cBody,new ASub(cParam,newAdr,cDs), new ASto(newAdr, aValue,aStore));
				}
			}
			
			if(fValue instanceof RefClosV) {
				RefClosV rcv = (RefClosV)fValue;
				String rcParam = rcv.getParam();
				RBMRCFAE rcBody = (RBMRCFAE)rcv.getBody();
				Dfs rcDs = rcv.getDS();
				
				int adr = lookup(((Id)app.getArg()).getId(), ds);
				return interp(rcBody,new ASub(rcParam,adr,rcDs), fStore);
			}
			
			throw new UndefinedASTException("Undefined AST: "+fValue.getClass().getSimpleName());
		}
		
		if(ast instanceof If0) {
			If0 if0 = (If0)ast;
			VS vs = (VS)interp(if0.getTestExpr(), ds,st);
			NumV testValue = (NumV)vs.getValue();
			
			if(testValue.getStrNum().equals("0"))
				return interp(if0.getThenExpr(),ds,st);
			else
				return interp(if0.getElseExpr(),ds,st);
		}
		
		if(ast instanceof Rec) {
			Rec rec = (Rec)ast;
			String boundId = rec.getId();
			RBMRCFAE funcExpr = rec.getFuncExpr();
			RBMRCFAE fstCall = rec.getfstCall();
			
			int newAdr = malloc(st);
			ASub newDs = new ASub(boundId,newAdr,ds);
			Value valueBox = new ClosureV(null,null,null);
			ARecSto newSt = new ARecSto(newAdr,valueBox,st);
			
			VS vs = (VS)interp(funcExpr,newDs,newSt);
			valueBox = vs.getValue();
			newSt.setValueBox(valueBox);
			
			return interp(fstCall, newDs, newSt);
		}
		
		if(ast instanceof NewBox) {
			NewBox newBox = (NewBox)ast;
			VS vs = (VS)interp(newBox.getValue(), ds, st);
			int newAdr = malloc(vs.getSt());
			
			return new VS(new BoxV(newAdr), new ASto(newAdr, vs.getValue(), vs.getSt()));
		}
		
		if(ast instanceof SetBox) {
			SetBox setBox = (SetBox)ast;
			VS vs1 = (VS)interp(setBox.getId(),ds,st);
			VS vs2 = (VS)interp(setBox.getValue(),ds,vs1.getSt());
			
			return new VS(vs2.getValue(), new ASto(((BoxV)vs1.getValue()).getAdr(), vs2.getValue(), vs2.getSt()));
		}
		
		if(ast instanceof OpenBox) {
			OpenBox openBox = (OpenBox)ast;
			VS vs = (VS)interp(openBox.getId(),ds,st);
			BoxV box = (BoxV)vs.getValue();
			
			return new VS(storeLookup(box.getAdr(),vs.getSt()), vs.getSt());
		}
		
		if(ast instanceof Seqn) {
			Seqn seqn = (Seqn)ast;
			VS vs1 = (VS)interp(seqn.getExpr1(),ds,st);
			VS vs2 = (VS)interp(seqn.getExpr2(),ds,vs1.getSt());
			
			return new VS(vs2.getValue(), vs2.getSt());
		}

		if(ast instanceof SetVar) {
			SetVar setVar = (SetVar)ast;
			int adr = lookup(setVar.getId(),ds);
			VS vs = (VS)interp(setVar.getValue(),ds,st);
			
			return new VS(vs.getValue(), new ASto(adr, vs.getValue(), vs.getSt()));
		}

		
		throw new UndefinedASTException("Undefined AST: "+ds.getClass().getSimpleName());
	}
	
	private int lookup(String name, Dfs ds){
		if(ds instanceof MtSub)
			throw new FreeIdentifierException("Free Identifier: "+name);
		
		ASub aSub = (ASub)ds;
		if(aSub.getName().equals(name))
			return aSub.getAdr();
		else
			return lookup(name, aSub.getDS());
	}
	
	private Value storeLookup(int adr, Store st) {
		if(st instanceof MtSto)
			throw new FreeAdressException("Free Identifier: "+adr);
		
		if(st instanceof ASto) {
			ASto aSto = (ASto)st;
			if(aSto.getAdr() == adr)
				return aSto.getV();
			else
				return storeLookup(adr, aSto.getRest());			
		}
		
		else if(st instanceof ARecSto) {
			ARecSto aRecSto = (ARecSto)st;
			if(aRecSto.getAdr() == adr)
				return aRecSto.getValueBox();
			else
				return storeLookup(adr, aRecSto.getRest());			
		}
		
		throw new UndefinedASTException("Undefined AST: "+st.getClass().getSimpleName());
	}
	
	private int malloc(Store st) {
		return maxAdress(st)+1;
	}
	
	private int maxAdress(Store st) {
		if(st instanceof MtSto)
			return 0;
		if(st instanceof ASto) {
			ASto aSto = (ASto)st;
			int adr = aSto.getAdr();
			return Max(adr, maxAdress(aSto.getRest()));
		}
		if(st instanceof ARecSto) {
			ARecSto aRecSto = (ARecSto)st;
			int adr = aRecSto.getAdr();
			return Max(adr, maxAdress(aRecSto.getRest()));
		}
		
		throw new UndefinedASTException("Undefined AST: "+st.getClass().getSimpleName());
	}
	
	private int Max(int a, int b) {
		return a>b?a:b;
	}
	
	private Value strict(Value v) {
		if(!(v instanceof ExprV))
			return v;
		
		ExprV exprV = (ExprV)v;
		if(exprV.getValue() instanceof DummyV) {
			VS vs = (VS)interp(exprV.getExpr(),exprV.getDs(),exprV.getSt());
			Value newV = strict(vs.getValue());
			exprV.setValue(newV);
		}
		
		return exprV.getValue();
	}
}
