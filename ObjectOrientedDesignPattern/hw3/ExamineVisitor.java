public class ExamineVisitor implements Visitor {
    private String[] lung = new String[]{"Lung cancer", "Asthma", "Tuberculosis"};
    private String[] stomach = new String[]{"Stomach Acid", "Gastritis", "Stomach cancer"};
    private String[] heart = new String[]{"Heart failure", "High Cholesterol", "Cardiac dysrhythmia"};

    @Override
    public void visit(LungRequest req){
        int idx = (int)(Math.random() * lung.length);
        System.out.println("Examining on Lung");
        System.out.println("Cause of "+lung[idx]+" found on lung");
        req.setExamine(lung[idx]);
    }

    @Override
    public void visit(HeartRequest req){
        int idx = (int)(Math.random() * heart.length);
        System.out.println("Examining on Heart");
        System.out.println("Cause of "+heart[idx]+" found on heart");
        req.setExamine(heart[idx]);
    }

    @Override
    public void visit(StomachRequest req){
        int idx = (int)(Math.random() * stomach.length);
        System.out.println("Examining on Stomach");
        System.out.println("Cause of "+stomach[idx]+" found on stomach");
        req.setExamine(stomach[idx]);
    }
}