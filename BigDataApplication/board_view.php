<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>BADGE</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/board.css">
</head>
<body> 
<header>
    <?php include "header.php";?>
</header>  
<section>
	<div id="main_img_bar">
        <img src="./img/main_logo2.png">
    </div>
   	<div id="board_box">
	    <h3 class="title">
			신고 게시판 > 내용보기
		</h3>
<?php
	$id  = $_GET["id"];
	$page  = $_GET["page"];

	$con = mysqli_connect("localhost", "team16", "team16", "team16");
	$sql = "select * from board where id=$id";
	$result = mysqli_query($con, $sql);

	$row = mysqli_fetch_array($result);
	$userid      = $row["userid"];
	$regist_day = $row["regist_day"];
	$station    = $row["station"];
	$content    = $row["content"];
	$hit          = $row["hit"];

	$content = str_replace(" ", "&nbsp;", $content);
	$content = str_replace("\n", "<br>", $content);

	$new_hit = $hit + 1;
	$sql = "update board set hit=$new_hit where id=$id";   
	mysqli_query($con, $sql);
?>		
	    <ul id="view_content">
			<li>
				<span class="col1"><b>신고 지역 :</b> <?=$station?>역 </span>
				<span class="col2"><?=$userid?> | <?=$regist_day?></span>
			</li>
			<li>
				<?=$content?>
			</li>		
	    </ul>
	    <ul class="buttons">
				<li><button onclick="location.href='board_list.php?page=<?=$page?>'">목록</button></li>
				<li><button onclick="location.href='board_modify_form.php?id=<?=$id?>&page=<?=$page?>'">수정</button></li>
				<li><button onclick="location.href='board_delete.php?id=<?=$id?>&page=<?=$page?>'">삭제</button></li>
				<li><button onclick="location.href='board_form.php'">글쓰기</button></li>
		</ul>
	</div> <!-- board_box -->
</section> 
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>
