package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.*;

public class Interpreter {

	public String interp(AST ast) {
		
		if(ast instanceof Num) {
			return ((Num)ast).getStrNum();
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			return "" + (Integer.parseInt(interp(add.getLhs())) + Integer.parseInt(interp(add.getRhs())));
		}
		
		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return "" + (Integer.parseInt(interp(sub.getLhs())) - Integer.parseInt(interp(sub.getRhs())));
		}
		
		if(ast instanceof With) {
			// [with (i v e) (interp (subst e i (interp v)))]
			With with = (With)ast;
			String i = with.getId();
			AST v = with.getValue();
			AST e = with.getExpression();
			
			return interp(subst(e,i,interp(v)));
		}
		
		if(ast instanceof Id) {
			throw new  RuntimeException("Free identifier");
		}
		
		return null;
	}
	
	private AST subst(AST ast, String idtf, String val) {
		if(ast instanceof Num) {
			return (Num)ast;
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			return new Add(subst(add.getLhs(),idtf,val), subst(add.getRhs(),idtf,val));
		}
		
		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return new Sub(subst(sub.getLhs(),idtf,val), subst(sub.getRhs(),idtf,val));
		}
		
		if(ast instanceof With) {
			// [with (i v e) (with i (subst v idtf val) (if (symbol=? i idtf) e (subst e idtf val)))]
			With with = (With)ast;
			String i = with.getId();
			AST v = with.getValue();
			AST e = with.getExpression();
			if(!i.equals(idtf))
				e = subst(e,idtf,val);
			
			return new With(i, subst(v,idtf,val), e);
		}
		
		if(ast instanceof Id) {
			// [id	(s) (if (symbol=? s idtf) (num val) wae)]
			Id id = (Id)ast;
			if(id.getId().equals(idtf))
				return new Num(val);
			else
				return id;
		}
		
		return null;
	}
}
