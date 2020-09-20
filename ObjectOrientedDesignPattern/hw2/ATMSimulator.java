import java.io.OutputStreamWriter;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;

class ATMSimulator{
    private static BufferedReader br;
    private static BufferedWriter bw;

    private static int memberCnt;
    private static ATM atm;
    private static List<Person> personList = new ArrayList<Person>();

    public static void main(String[] args) throws IOException, InterruptedException {
        br = new BufferedReader(new InputStreamReader(System.in));
        bw = new BufferedWriter(new OutputStreamWriter(System.out));

        bw.write("Initial Balance: ");
        bw.flush();
        int initBalance = Integer.parseInt(br.readLine());

        bw.write("The number of family members: ");
        bw.flush();
        int cnt = Integer.parseInt(br.readLine());

        init(initBalance, cnt);
        bw.write("Initial Balance is $"+Integer.toString(initBalance)+"\n");

        for(Person person: personList){
            person.start();
        }

        for(Person person: personList){
            person.join();
        }

        atm.printResult();

        bw.close();
        br.close();
    }

    public static void init(int initBalance, int cnt){
        if(initBalance >= 0 && initBalance <= ATM.MAX_INIT_BALANCE)
            atm = new ATM(initBalance, bw);
        else
            throw new AssertionError("Initial Balance should be between 0~100");

        if(cnt >= 1 && cnt <= Person.MAX_MEMBER_CNT)
            memberCnt = cnt;
        else
            throw new AssertionError("Number of Family Members should be between 1~6");

        for(int i=0;i<memberCnt; i++)
            personList.add(Person.getInstance(atm));
    }
}