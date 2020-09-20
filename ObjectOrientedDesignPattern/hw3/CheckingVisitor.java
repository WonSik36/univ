public class CheckingVisitor implements Visitor {
    private String[] lung = new String[]{"Lung cancer", "Asthma", "Tuberculosis"};
    private String[] stomach = new String[]{"Stomach Acid", "Gastritis", "Stomach cancer"};
    private String[] heart = new String[]{"Heart failure", "High Cholesterol", "Cardiac dysrhythmia"};

    @Override
    public void visit(LungRequest req){
        int idx = (int)(Math.random() * lung.length);
        System.out.println("Checking on Lung");
        System.out.println("Chance of "+lung[idx]+" on lung");
        req.setCheck(lung[idx]);
    }

    @Override
    public void visit(HeartRequest req){
        int idx = (int)(Math.random() * heart.length);
        System.out.println("Checking on Heart");
        System.out.println("Chance of "+heart[idx]+" on heart");
        req.setCheck(heart[idx]);
    }

    @Override
    public void visit(StomachRequest req){
        int idx = (int)(Math.random() * stomach.length);
        System.out.println("Checking on Stomach");
        System.out.println("Chance of "+stomach[idx]+" on stomach");
        req.setCheck(stomach[idx]);
    }
}