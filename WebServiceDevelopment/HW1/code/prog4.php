<?php
  //$num 배열 요소의 총개수
  $num = 100;
  //배열 요소를 100개로 하여 0으로 채워진 배열 선언 
  $arr = array_fill(0, $num, 0);
  //배열을 랜덤한 수로 채워줌
  fill_arr($arr);
  //배열을 출력
  print_arr($arr);
  //합계를 출력
  echo "</br></br>Sum of given array: ".sum_arr($arr);

  //배열을 출력하는 함수
  function print_arr($arr){
    $length = sizeof($arr);

    for($i=0; $i<$length; $i++){
      echo $arr[$i]." ";

      // 10번째 인자 출력 후 줄 바꿈
      if($i % 10 == 9)
        echo "</br></br>";
    }
  }

  //배열을 채워주는 함수 -> 함수 포인터는 없나?
  function fill_arr(&$arr){
    for($i=0; $i<sizeof($arr); $i++)
      //0에서 100사이의 랜덤한 수를 배열에 넣어줌
      $arr[$i] = rand(0,100);
  }

  //배열의 합을 구하는 함수
  function sum_arr($arr){
    $sum = 0;

    for($i=0; $i<sizeof($arr); $i++)
      $sum += $arr[$i];

    return $sum;
  }
 ?>
