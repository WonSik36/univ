public class Person extends Thread{
    public static final int MAX_DEPOSIT = 50;
    public static final int MAX_WITHDRAWL = 80;

    public static final int MAX_MEMBER_CNT = 6;
    public static int MEMBER_CNT = 0;

    private static final int MAX_CNT = 20;  // max count of deposit and withdrawl allowed
    private static int currentCnt = 0;

    private ATM atm;
    private int num;

    public static Person getInstance(ATM atm){
        if(MEMBER_CNT >= MAX_MEMBER_CNT)
            throw new AssertionError("Number of Family Members exceeds 6");
        
        MEMBER_CNT++;

        return new Person(atm, MEMBER_CNT);
    }

    private Person(ATM atm, int num){
        this.atm = atm;
        this.num = num;
    }

    @Override
    public void run(){
        try{
            while(true){
                // if(!isValid())
                //     break;
                boolean isDeposit = getRandomBool();
                int money = getRandomNumber(isDeposit);
        
                if(isDeposit){
                    atm.storeMoney(money, this.num);
                }else{
                    atm.retrieveMoney(money, this.num);
                }
            }
        }catch(RuntimeException e){}
    }

    private static synchronized boolean isValid(){
        if(currentCnt == MAX_CNT){
            return false;
        }else if(currentCnt > MAX_CNT){
            throw new AssertionError("Count of Store and Retrieve Money Exceed MAX_CNT");
        }else{
            currentCnt++;
            return true;
        }
    }

    private int getRandomNumber(boolean isDeposit){
        int rand;

        if(isDeposit){
            rand = (int)(Math.random() * (MAX_DEPOSIT+1));
        }else{
            rand = (int)(Math.random() * (MAX_WITHDRAWL+1));
        }

        return rand;
    }

    private boolean getRandomBool(){
        int rand = (int)(Math.random() * 2);

        if(rand == 0)
            return true;
        else
            return false;
    }
}