<?php
    $id   = $_POST["id"];
    $password = $_POST["password"];
    $name = $_POST["name"];
    $gender = $_POST["gender"];
    $birth1  = $_POST["birth1"];
    $birth2  = $_POST["birth2"];
    $birth3  = $_POST["birth3"];
    $email1  = $_POST["email1"];
    $email2  = $_POST["email2"];

    $birth = $birth1.".".$birth2.".".$birth3;

    $email = $email1."@".$email2;
  

              
    $con = mysqli_connect("localhost", "team16", "team16", "team16");

	$sql = "insert into user(id, name, password,email, gender,birth) ";
	$sql .= "values('$id', '$name', '$password', '$email','$gender','$birth')";

	mysqli_query($con, $sql);  // $sql 에 저장된 명령 실행
    mysqli_close($con);     

    echo "
	      <script>
	          location.href = 'index.php';
	      </script>
	  ";
?>

   
