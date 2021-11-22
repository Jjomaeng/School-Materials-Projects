<meta charset="utf-8">
<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    if (isset($_SESSION["username"])) $username = $_SESSION["username"];
    else $username = "";


    $pregnant = $_POST["pregnant"];
    $useHour = $_POST["useHour"];
    $sit = $_POST["sit"];

    $con = mysqli_connect("localhost", "team16", "team16", "team16");

    $sql = "insert into user_input (user_id,pregnant,use_hour,sit,line_name) values 
    ('".$userid."',".$pregnant.",'".$useHour."',".$sit.", 'line2')";

    mysqli_query($con, $sql);

    mysqli_close($con);                // DB 연결 끊기

        echo "
       <script>
        location.href = 'index.php';
       </script>
    ";

?>
