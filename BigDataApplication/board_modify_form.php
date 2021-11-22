<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>BADGE</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/board.css">
<script>
  function check_input() {
      if (!document.board_form.station.value)
      {
          alert("역을 선택하세요!");
          document.board_form.station.focus();
          return;
      }
      if (!document.board_form.content.value)
      {
          alert("내용을 입력하세요!");    
          document.board_form.content.focus();
          return;
      }
      document.board_form.submit();
   }
</script>
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
	    <h3 id="board_title">
	    		신고 게시판 > 수정하기
		</h3>
<?php
	$id  = $_GET["id"];
	$page = $_GET["page"];
	
	$con = mysqli_connect("localhost", "team16", "team16", "team16");
	$sql = "select * from board where id=$id";
	$result = mysqli_query($con, $sql);
	$row = mysqli_fetch_array($result);
	$station    = $row["station"];
	$content    = $row["content"];		
?>
	    <form  name="board_form" method="post" action="board_modify.php?id=<?=$id?>&page=<?=$page?>" enctype="multipart/form-data">
	    	 <ul id="board_form">

	    		<li>
	    			<span class="col1">지하철역 : </span>
	    			<span class="col2"><input name="station" type="text" value="<?=$station?>"></span>
	    		</li>	  

	    		<li id="text_area">	
	    			<span class="col1">내용 : </span>
	    			<span class="col2">
	    				<textarea name="content"><?=$content?></textarea>
	    			</span>
	    		</li>

	    			    	    </ul>
	    	<ul class="buttons">
				<li><button type="button" onclick="check_input()">수정하기</button></li>
				<li><button type="button" onclick="location.href='board_list.php'">목록</button></li>
			</ul>
	    </form>
	</div> <!-- board_box -->
</section> 
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>
