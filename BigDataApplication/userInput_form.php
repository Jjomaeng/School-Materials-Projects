<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>BADGE</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/board.css">
<script>
  function check_input() {
      if (!document.userinput_form.pregnant.value)
      {
          alert("임신 여부를 선택하세요!");
          document.userinput_form.pregnant.focus();
          return;
      }
      if (!document.userinput_form.useHour.value)
      {
          alert("이용시간대를 선택하세요!");
          document.userinput_form.useHour.focus();
          return;
      }
      if (!document.userinput_form.sit.value)
      {
          alert("착석여부를 선택하세요!");    
          document.userinput_form.sit.focus();
          return;
      }
      document.userinput_form.submit();
   }
</script>
</head>
<body> 
<header>
    <?php include "header.php";?>
</header>

<?php
   if (!$userid )
   {
      echo("<script>
            alert('로그인 후 이용해주세요!');
            history.go(-1);
            </script>
         ");
      exit;
   }
?>
  
<section>
	<div id="main_img_bar">
        <img src="./img/main_logo2.png">
    </div>
   	<div id="board_box">
	    <h3 id="board_title">
	    		사용자 입력
		</h3>
	    <form  name="userinput_form" method="post" action="userinput_insert.php" enctype="multipart/form-data">
	    	 <ul id="board_form">
				<li>
					<span class="col1">이름 : </span>
					<span class="col2"><?=$userid?></span>
				</li>		

	    		<li>
	    			<span class="col1">임산부 여부 : </span>
	    			<span class="col2"><select name = "pregnant">
									<option value = "" disabled selected>선택하세요!</option>
									<option value = "1" >예</option>
									<option value = "0" >아니오</option>
								</select>
							</span>
	    		</li>


	    		<li>
	    			<span class="col1">이용시간대 : </span>
	    			<span class="col2"><select name = "useHour">
									<option value = "" disabled selected>선택하세요!</option>
	                <option value="06:00 이전">06:00 이전</option>
	                <option value="06:00~07:00">06:00~07:00</option>
	                <option value="07:00~08:00">07:00~08:00</option>
	                <option value="08:00~09:00">08:00~09:00</option>
	                <option value="09:00~10:00">09:00~10:00</option>
	                <option value="10:00~11:00">10:00~11:00</option>
	                <option value="11:00~12:00">11:00~12:00</option>
	                <option value="12:00~13:00">12:00~13:00</option>
	                <option value="13:00~14:00">13:00~14:00</option>
	                <option value="14:00~15:00">14:00~15:00</option>
	                <option value="15:00~16:00">15:00~16:00</option>
	                <option value="16:00~17:00">16:00~17:00</option>
	                <option value="17:00~18:00">17:00~18:00</option>
	                <option value="18:00~19:00">18:00~19:00</option>
	                <option value="19:00~20:00">19:00~20:00</option>
	                <option value="20:00~21:00">20:00~21:00</option>
	                <option value="21:00~22:00">21:00~22:00</option>
	                <option value="22:00~23:00">22:00~23:00</option>
	              </select>
					</span>
					</li>

	    		<li>
	    			<span class="col1">착석 여부 : </span>
	    			<span class="col2"><select name = "sit">
									<option value = "" disabled selected>선택하세요!</option>
									<option value = "1" >예</option>
									<option value = "0" >아니오</option>
								</select>
							</span>
	    		</li>
	    	    </ul>
	    	<ul class="buttons">
				<li><button type="button" onclick="check_input()">완료</button></li>
			</ul>
	    </form>
	</div> <!-- board_box -->
</section> 
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>
