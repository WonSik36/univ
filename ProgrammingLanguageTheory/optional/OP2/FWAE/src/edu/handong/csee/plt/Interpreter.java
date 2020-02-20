package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.*;

public class Interpreter {

	public AST interp(AST ast) {
		
		if(ast instanceof Num) {
			return ((Num)ast);
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			int lhs = Integer.parseInt(((Num)interp(add.getLhs())).getStrNum());
			int rhs = Integer.parseInt(((Num)interp(add.getRhs())).getStrNum());
			Num res = new Num(Integer.toString(lhs+rhs));
			
			return res;
		}
		
		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			int lhs = Integer.parseInt(((Num)interp(sub.getLhs())).getStrNum());
			int rhs = Integer.parseInt(((Num)interp(sub.getRhs())).getStrNum());
			Num res = new Num(Integer.toString(lhs-rhs));
			
			return res;
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
		
		if(ast instanceof Fun) {
			return ((Fun)ast);
		}
		
		if(ast instanceof App) {
			App app = (App)ast;
			Fun ftn = ((Fun)app.getFtn());
			return interp(subst(ftn.getBody(), ftn.getParam(), interp(app.getArg())));
		}
		
		return null;
	}
	
	private AST subst(AST ast, String idtf, AST val) {
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
				return val;
			else
				return id;
		}
		
		if(ast instanceof Fun) {
			// [fun (id body) (if (equal? idtf id) exp (fun id (subst body idtf val)))]))
			Fun fun = (Fun)ast;
			String param = fun.getParam();
			AST body = fun.getBody();
			
			if(param.equals(idtf))
				return ast;
			else
				return new Fun(param, subst(body,idtf,val));
		}
		
		
		if(ast instanceof App) {
			// [app (f arg) (app (subst f idtf val) (subst arg idtf val))]
			App app = (App)ast;
			AST ftn = app.getFtn();
			AST arg = app.getArg();
			
			return new App(subst(ftn,idtf,val), subst(arg,idtf,val));
		}
		
		return null;
	}
}
