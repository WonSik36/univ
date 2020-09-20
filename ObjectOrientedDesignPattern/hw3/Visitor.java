public interface Visitor {
    public void visit(LungRequest req);
    public void visit(HeartRequest req);
    public void visit(StomachRequest req);
}