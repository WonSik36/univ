

public class Practice1{
    public static void main(String[] args)throws Exception{
        final double percent = 0.2;
        final double target = 0.004;
        int N = 10;
        double result = 0;

        while(result < target){
            result = 0;
            N++;
            for(int i=11;i<=N;i++){
                double ret = combination(N, i)*Math.pow(percent,i)*Math.pow(1.0-percent,N-i);
                result += ret;
                // System.out.printf("i: %d, ret: %.20f\n",i,ret);
            }
            System.out.printf("N: %d, result: %.20f\n",N,result);
        }

    }

    public static double combination(int n, int k)throws Exception{
        int a = n;
        double ret = 1;
        while(a>k){
            ret *= a--;
        }
        ret = ret / factorial(n-k);
        if(ret<0)
            throw new Exception("overflow");
        return ret;
    }

    public static double factorial(int n)throws Exception{
        double ret = 1;
        while(n>1){
            ret *= n--;
        }
        if(ret<0)
            throw new Exception("overflow");
        return ret;
    }
}