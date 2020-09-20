import java.util.List;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args){
        List<Request> reqList = new ArrayList<>();
        reqList.add(new LungRequest(new LungSpecialist()));
        reqList.add(new HeartRequest(new HeartSpecialist()));
        reqList.add(new StomachRequest(new StomachSpecialist()));

        List<Visitor> visitList = new ArrayList<>();
        visitList.add(new CheckingVisitor());
        visitList.add(new ExamineVisitor());
        visitList.add(new TreatmentVisitor());

        for(Visitor visitor : visitList){
            for(Request req : reqList){
                req.accept(visitor);
            }
        }
    }
    
}