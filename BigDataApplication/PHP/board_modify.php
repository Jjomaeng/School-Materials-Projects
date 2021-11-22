<?php
    $id = $_GET["id"];
    $page = $_GET["page"];

    $station = $_POST["station"];
    $content = $_POST["content"];
          
    $con = mysqli_connect("localhost", "team16", "team16", "team16");
    $sql = "update board set station='$station', content='$content' ";
    $sql .= " where id=$id";
    mysqli_query($con, $sql);

    mysqli_close($con);     

    echo "
          <script>
              location.href = 'board_list.php?page=$page';
          </script>
      ";
?>

   
