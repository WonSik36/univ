import java.util.Observable;
import java.util.Observer;

public class LungSpecialist implements Observer{
    @Override
    public void update(Observable o, Object arg) {
        System.out.println("Lung specialist received : " + arg);   
    }
}