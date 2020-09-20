import java.util.Observable;
import java.util.Observer;

public class StomachSpecialist implements Observer{
    @Override
    public void update(Observable o, Object arg) {
        System.out.println("Stomach specialist received : " + arg);   
    }
}