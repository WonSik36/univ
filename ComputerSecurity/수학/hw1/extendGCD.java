/*
    Computer Security Class
    showing extended euclidean algorithm
*/

public class extendGCD{

    public static void main(String[] args){
        int a = Integer.parseInt(args[0]);
        int b = Integer.parseInt(args[1]);
        int[] res = extendedEuclidean(a, b);
        System.out.printf("result: d:%d, s:%d, t:%d\n",res[0],res[1],res[2]);
        System.out.printf("(%d)*(%d) + (%d)*(%d) = %d\n",a,res[1],b,res[2],a*res[1]+b*res[2]);
    }

    // find s*a+t*b = GCD(a,b)
    public static int[] extendedEuclidean(int a, int b){
        int[] r = new int[]{a,b};
        int[] s = new int[]{1,0};
        int[] t = new int[]{0,1};

        while(r[1]>0){
            int Q = r[0] / r[1];

            int prevR1 = r[0];
            int prevR2 = r[1];
            int R = r[0] - Q*r[1];
            r[0] = r[1];
            r[1] = R;

            int prevS1 = s[0];
            int prevS2 = s[1];
            int S = s[0] - Q*s[1];
            s[0] = s[1];
            s[1] = S;

            int prevT1 = t[0];
            int prevT2 = t[1];
            int T = t[0] - Q*t[1];
            t[0] = t[1];
            t[1] = T;
            System.out.printf("Q:%d r1:%d r2:%d R:%d\n",Q,prevR1,prevR2,R);
            System.out.printf("s1:%d s2:%d S:%d t1:%d t2:%d T:%d\n\n",prevS1,prevS2,S,prevT1,prevT2,T);
        }
        System.out.printf("r1:%d r2:%d, s1:%d s2:%d, t1:%d t2:%d\n\n",r[0],r[1],s[0],s[1],t[0],t[1]);
        // s*a+t*b = GCD(a,b)
            return new int[]{r[0],s[0],t[0]};
    }
}