<?php
  // $num -> 배열의 총 개수
  $num = 20;
  //총 요소 20개로 이루어진 배열에 모두 0을 넣어 선언
  $fibo_arr = array_fill(0, $num, 0);
  //배열을 피보나치 수열로 채워줌
  fill_arr($fibo_arr);
  //배열을 프린트함
  print_arr($fibo_arr);

  //배열을 채워주는 함수 -> 함수 포인터는 없나?
  function fill_arr(&$arr){
    for($i=0; $i<sizeof($arr); $i++)
      $arr[$i] = fibo($i+1);
  }

  // 배열을 출력하는 함수
  function print_arr($arr){
    $length = sizeof($arr);

    for($i=0; $i<$length; $i++){
      echo $arr[$i]." ";

      // 10번째 인자 출력 후 줄 바꿈
      if($i % 10 == 9)
        echo "</br></br>";
    }
  }

  // 피보나치 수열을 생성하는 함수
  function fibo($num){
    if($num == 1)
      return 0;
    else if($num == 2)
      return 1;
    else
      return fibo($num-1) + fibo($num-2);
  }
 ?>
