how to execute the program (In windows OS)

***** 1. change directory *****
cd [your path]\[Language]\src
  ex) cd [your path]\AE\src 

***** 2. compile java file *****
in AE, WAE, FWAE
javac .\edu\handong\csee\plt\*.java .\edu\handong\csee\plt\ast\*.java

in FAE
javac .\edu\handong\csee\plt\*.java .\edu\handong\csee\plt\ast\*.java .\edu\handong\csee\plt\astvalue\*.java .\edu\handong\csee\plt\dfs\*.java

in RCFAE
javac .\edu\handong\csee\plt\*.java .\edu\handong\csee\plt\ast\*.java .\edu\handong\csee\plt\ast\value\*.java .\edu\handong\csee\plt\ast\dfs\*.java .\edu\handong\csee\plt\ast\rcfae\*.java .\edu\handong\csee\plt\exception\*.java

in RBMRCFAE, LRBMRCFAE
javac .\edu\handong\csee\plt\*.java .\edu\handong\csee\plt\ast\*.java .\edu\handong\csee\plt\ast\dfs\*.java .\edu\handong\csee\plt\ast\rbmrcfae\*.java .\edu\handong\csee\plt\ast\store\*.java .\edu\handong\csee\plt\ast\value\*.java .\edu\handong\csee\plt\ast\vs\*.java .\edu\handong\csee\plt\exception\*.java

***** 3. run Main class *****
java edu.handong.csee.plt.Main [option] "code"

option
-p : execute only parser not interpreter

***** Implementation of Laziness *****

1. I applied laziness to add, sub, mult
2. I changed code of fun and app case in interp function of Interpreter
3. Parameter of recursion function is exprV (after first try) and it DOES NOT have DefrdSub and Store for get value when strict function executed
4. Therefore, I put DefrdSub to parameter identifier and new address in code of fun
   And in code of app, I only put new address and exprV to Store
5. It make recursion function work, such as sum and factorial,
   but when I execute fibonacci fucntion, it makes infinte loop, because it overwrite value of exprV
   (fibo(3) makes fibo(2) and fibo(1). fibo(1) has store which is reflected by store of fibo(2))