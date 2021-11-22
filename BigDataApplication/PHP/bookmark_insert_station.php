<meta charset="utf-8">
<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    if (isset($_SESSION["username"])) $username = $_SESSION["username"];
    else $username = "";


    $station = $_POST["station_id"];

    $con = mysqli_connect("localhost", "team16", "team16", "team16");

    $sql = "insert into station_likes(user_id,station_id) ";
    $sql .= "values('$userid', '$station')";

    mysqli_query($con, $sql);

    mysqli_close($con);                // DB 연결 끊기

    echo "
       <script>
        location.href = 'bookmark_list_station.php?station=$station';
       </script>
    ";

?>
