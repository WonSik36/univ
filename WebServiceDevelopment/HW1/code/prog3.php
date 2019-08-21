<?php
  $book_num = array(
    "ECE20009" => "Web Service Development",
    "ECE20018" => "C++ Programing",
    "ITP30003" => "Computer Architecture and Organization",
    "ECE20061" => "Engineering Electromagnetics",
  );

  //Key function asort : sort an array by values
  asort($book_num);
  print_dict($book_num);

  function print_dict($arr){
    foreach($arr as $key => $value){
      //배열을 value와 key 순으로 출력
      echo "Book ".$value." : ".$key."</br>";
    }
  }
 ?>
