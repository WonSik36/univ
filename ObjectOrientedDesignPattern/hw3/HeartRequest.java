import java.util.Observable;
import java.util.Observer;

public class HeartRequest extends Observable implements Request {
    private String check;
    private String examine;
    private String treatment;

    public HeartRequest(Observer obs) {
        super.addObserver(obs);
    }

    public void accept(Visitor visitor){
        visitor.visit(this);
    }

    public void setCheck(String check){
        this.check = check;
        setChanged();
        notifyObservers("Chance of "+this.check);
    }

    public String getCheck(){
        return this.check;
    }

    public void setExamine(String examine){
        this.examine = examine;
        setChanged();
        notifyObservers(this.examine + " found");
    }

    public String getExamine(){
        return this.examine;
    }

    public void setTreatment(String treatment){
        this.treatment = treatment;
        setChanged();
        notifyObservers(this.treatment);
    }

    public String getTreatment(){
        return this.treatment;
    }
}