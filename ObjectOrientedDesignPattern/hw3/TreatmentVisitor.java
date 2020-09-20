public class TreatmentVisitor implements Visitor {
    private String[] treat = new String[]{"Medicine", "Proper food and exercise", "Operation"};

    @Override
    public void visit(LungRequest req){
        int idx = (int)(Math.random() * treat.length);
        System.out.println("Treatment Recommendation for lung");
        System.out.println(treat[idx]+" recommended for lung");
        req.setTreatment(treat[idx]);
    }

    @Override
    public void visit(HeartRequest req){
        int idx = (int)(Math.random() * 3);
        System.out.println("Treatment Recommendation for heart");
        System.out.println(treat[idx]+" recommended for heart");
        req.setTreatment(treat[idx]);
    }

    @Override
    public void visit(StomachRequest req){
        int idx = (int)(Math.random() * 3);
        System.out.println("Treatment Recommendation for stomach");
        System.out.println(treat[idx]+" recommended for stomach");
        req.setTreatment(treat[idx]);
    }
}