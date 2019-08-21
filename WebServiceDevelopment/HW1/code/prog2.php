<?php
  for($i=1; $i<=100; $i++){
    //숫자가 5로 나누어지면
    if($i%5==0){
      //3으로도 나누어지는지 확인
      if($i%3==0)
        //3으로도 나눠지면 FizzBuzz 출력
        echo "FizzBuzz</br>";
      //5만으로 나눠지면 Buzz 출력
      else
        echo "Buzz</br>";
    }
    //3으로만 나눠지면 Fizz 출력
    else if($i%3==0)
      echo "Fizz</br>";
    //3과 5로 나눠지지 않으면 숫자 출력
    else
      echo $i."</br>";
  }

 ?>
