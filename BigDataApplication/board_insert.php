<meta charset="utf-8">
<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    if (isset($_SESSION["username"])) $username = $_SESSION["username"];
    else $username = "";

    if ( !$userid )
    {
        echo("
                    <script>
                    alert('신고하기는 로그인 후 이용해 주세요!');
                    history.go(-1)
                    </script>
        ");
                exit;
    }

    $station = $_POST["station"];
    $content = $_POST["content"];

	$station = htmlspecialchars($station, ENT_QUOTES);
	$content = htmlspecialchars($content, ENT_QUOTES);

	$regist_day = date("Y-m-d (H:i)" );  // 현재의 '년-월-일-시-분'을 저장
	
	$con = mysqli_connect("localhost", "team16", "team16", "team16");

	$sql = "insert into board (userid, station,content, regist_day, hit) ";
	$sql .= "values('$userid', '$station','$content', '$regist_day', 0)";

	mysqli_query($con, $sql);

	mysqli_close($con);                // DB 연결 끊기

	echo "
	   <script>
	    location.href = 'board_list.php';
	   </script>
	";
?>

  
