import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Objects;

public class ATM {
    private BufferedWriter bw = null;
    public static final int MAX_INIT_BALANCE = 100;
    public static final int MAX_DENIAL_CNT = 4;
    private int balance = -1;
    private int totalSaved;
    private int totalSpent;
    private int denialCount;

    public ATM(int initBalance, BufferedWriter bw){
        this.balance = initBalance;
        this.bw = Objects.requireNonNull(bw);
        this.totalSaved = initBalance;
        this.totalSpent = 0;
        this.denialCount = 0;
    }

    public void printResult() throws IOException{
        String str = String.format("Total Saved: $%d, Total Spent: $%d\n", totalSaved, totalSpent);
        bw.write(str);
        str = String.format("Current balance: $%d\n", balance);
        bw.write(str);
    }

    public synchronized void retrieveMoney(int money, int num) {
        if(denialCount >= MAX_DENIAL_CNT)
            throw new RuntimeException("Denial Count is reached at MAX DENIAL COUNT");

        try{
            if(money > balance){
                String str = String.format("family member %d: trying to retrieve $%d\n", num, money);
                bw.write(str);
                str = "Not allowed, balance is not sufficient!\n";
                bw.write(str);
                denialCount++;
            }else{
                balance -= money;
                totalSpent += money;
                String str = String.format("family member %d: retrieving -$%d\n", num, money);
                bw.write(str);
                str = String.format("New Balance: $%d\n", balance);
                bw.write(str);
            }
        }catch(IOException e){
            throw new RuntimeException(e);
        }
    }

    public synchronized void storeMoney(int money, int num){
        try{
            balance += money;
            totalSaved += money;
            String str = String.format("family member %d: storing +$%d\n", num, money);
            bw.write(str);
            str = String.format("New Balance: $%d\n", balance);
            bw.write(str);
        }catch(IOException e){
            throw new RuntimeException(e);
        }
    }
}