import java.util.Observable;
import java.util.Observer;

public class HeartSpecialist implements Observer{
    @Override
    public void update(Observable o, Object arg) {
        System.out.println("Heart specialist received : " + arg);   
    }
}