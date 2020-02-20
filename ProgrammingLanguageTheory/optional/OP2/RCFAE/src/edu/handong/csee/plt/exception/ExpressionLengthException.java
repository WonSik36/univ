package edu.handong.csee.plt.exception;

public class ExpressionLengthException extends BadSyntaxException {
	private int size;
	
	public ExpressionLengthException(String err, int size) {
		super(err);
		this.size = size;
	}
	
	@Override
	public String getMessage() {
		String ret = " Expression Size: "+size;
		return super.getMessage()+ret;
	}
}
