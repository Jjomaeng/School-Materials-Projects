<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    if (isset($_SESSION["username"])) $username = $_SESSION["username"];
    else $username = "";
?>		
        <div id="top">
            <h3>
                <a href="index.php">BADGE</a>
            </h3>
            <ul id="top_menu">  
<?php
    if(!$userid) {
?>                
                <li><a href="member_form.php">회원 가입</a> </li>
                <li> | </li>
                <li><a href="login_form.php">로그인</a></li>
<?php
    } else {
                $logged = $username."(".$userid.")님";
?>
                <li><?=$logged?> </li>
                <li> | </li>
                <li><a href="logout.php">로그아웃</a> </li>
            
<?php
    }
?>

            </ul>
        </div>
        <div id="menu_bar">

            <ul>  
                <li><a href="index.php">HOME</a></li>
                <li><a href="congestion_form.php">혼잡도</a></li>
                <li><a href="util_form.php">통계량</a></li>
                <li><a href="userInput_form.php">사용자 입력</a></li>
                <li><a href="bookmark_form.php">즐겨찾기</a></li>                                
                <li><a href="board_form.php">신고하기</a></li>
            </ul>
        </div>