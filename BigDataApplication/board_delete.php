<?php

    $id   = $_GET["id"];
    $page   = $_GET["page"];

    $con = mysqli_connect("localhost", "team16", "team16", "team16");
    $sql = "select * from board where id = $id";
    $result = mysqli_query($con, $sql);
    $row = mysqli_fetch_array($result);


    $sql = "delete from board where id = $id";
    mysqli_query($con, $sql);
    mysqli_close($con);

    echo "
	     <script>
	         location.href = 'board_list.php?page=$page';
	     </script>
	   ";
?>

