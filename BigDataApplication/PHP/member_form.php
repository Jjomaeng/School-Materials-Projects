<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>BADGE</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/member.css">
<script>
   function check_input()
   {
      if (!document.member_form.id.value) {
          alert("아이디를 입력하세요!");    
          document.member_form.id.focus();
          return;
      }

      if (!document.member_form.password.value) {
          alert("비밀번호를 입력하세요!");    
          document.member_form.password.focus();
          return;
      }


      if (!document.member_form.name.value) {
          alert("이름을 입력하세요!");    
          document.member_form.name.focus();
          return;
      }

      if (!document.member_form.email1.value) {
          alert("이메일 주소를 입력하세요!");    
          document.member_form.email1.focus();
          return;
      }

      if (!document.member_form.email2.value) {
          alert("이메일 주소를 입력하세요!");    
          document.member_form.email2.focus();
          return;
      }
      if (!document.member_form.gender.value) {
          alert("성별을 입력하세요!");    
          document.member_form.gender.focus();
          return;
      }

       if (!document.member_form.birth1.value) {
          alert("출생년도를 입력하세요!");    
          document.member_form.birth1.focus();
          return;
      }

      if (!document.member_form.birth2.value) {
          alert("출생월을 입력하세요!");    
          document.member_form.birth2.focus();
          return;
      }

      if (!document.member_form.birth3.value) {
          alert("출생일을 입력하세요!");    
          document.member_form.birth3.focus();
          return;
      }




      document.member_form.submit();
   }

   function reset_form() {
      document.member_form.id.value = "";  
      document.member_form.password.value = "";
      document.member_form.name.value = "";
      document.member_form.gender.value = "";
      document.member_form.email1.value = "";
      document.member_form.email2.value = "";
      document.member_form.birth1.value = "";
      document.member_form.birth2.value = "";
      document.member_form.birth3.value = "";
      document.member_form.id.focus();
      return;
   }

   function check_id() {
     window.open("member_check_id.php?id=" + document.member_form.id.value,
         "IDcheck",
          "left=700,top=300,width=350,height=200,scrollbars=no,resizable=yes");
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
        <div id="main_content">
      		<div id="join_box">
          	<form  name="member_form" method="post" action="member_insert.php">
			    <h2>회원 가입</h2>
    		    	<div class="form id">
				        <div class="col1">아이디</div>
				        <div class="col2">
							<input type="text" name="id">
				        </div>  
				        <div class="col3">
				        	<a href="#"><img src="./img/check_id.gif" 
				        		onclick="check_id()"></a>
				        </div>                 
			       	</div>
			       	<div class="clear"></div>

			       	<div class="form">
				        <div class="col1">비밀번호</div>
				        <div class="col2">
							<input type="password" name="password">
				        </div>                 
			       	</div>
			       	<div class="clear"></div>

			       	<div class="form">
				        <div class="col1">이름</div>
				        <div class="col2">
							<input type="text" name="name">
				        </div>                 
			       	</div>
			       	<div class="clear"></div>

			       	<div class="form">
				        <div class="col1">성별</div>
				        <div class="col2">
								<select name = "gender">
									<option value = "" disabled selected>선택하세요!</option>
									<option value = "1" >여성</option>
									<option value = "2" >남성</option>
								</select>	
				        </div>                 
			       	</div>
			       	<div class="clear"></div>

			       	<div class="form">
				        <div class="col1">출생년도</div>
				        <div class="col2">
				        <select name = "birth1">
									<option value = "" disabled selected>선택하세요!</option>
									<option value = "1980" >1980</option>
									<option value = "1981" >1981</option>
									<option value = "1982" >1982</option>
									<option value = "1983" >1983</option>
									<option value = "1984" >1984</option>
									<option value = "1985" >1985</option>
									<option value = "1986" >1986</option>
									<option value = "1987" >1987</option>
									<option value = "1988" >1988</option>
									<option value = "1989" >1989</option>
									<option value = "1990" >1990</option>
									<option value = "1991" >1991</option>
									<option value = "1992" >1992</option>
									<option value = "1993" >1993</option>
									<option value = "1994" >1994</option>
									<option value = "1995" >1995</option>
									<option value = "1996" >1996</option>
									<option value = "1997" >1997</option>
									<option value = "1998" >1998</option>
									<option value = "1999" >1999</option>
									<option value = "2000" >2000</option>
									<option value = "2001" >2001</option>
									<option value = "2002" >2002</option>
									<option value = "2003" >2003</option>
									<option value = "2004" >2004</option>
									<option value = "2005" >2005</option>
									<option value = "2006" >2006</option>
									<option value = "2007" >2007</option>
									<option value = "2008" >2008</option>
									<option value = "2009" >2009</option>
									<option value = "2010" >2010</option>
									<option value = "2011" >2011</option>
									<option value = "2012" >2012</option>
									<option value = "2013" >2013</option>
									<option value = "2014" >2014</option>
									<option value = "2015" >2015</option>
									<option value = "2016" >2016</option>
									<option value = "2017" >2017</option>
									<option value = "2018" >2018</option>
									<option value = "2019" >2019</option>
									<option value = "2020" >2020</option>
									<option value = "2021" >2021</option>


								</select>년 
							
								<select name = "birth2">
									<option value = "" disabled selected>선택하세요!</option>
									<option value = "01" >01</option>
									<option value = "02" >02</option>
									<option value = "03" >03</option>
									<option value = "04" >04</option>
									<option value = "05" >05</option>
									<option value = "06" >06</option>
									<option value = "07" >07</option>
									<option value = "08" >08</option>
									<option value = "09" >09</option>
									<option value = "10" >10</option>
									<option value = "11" >11</option>
									<option value = "12" >12</option>
								</select>월 

								<select name = "birth3">
									<option value = "" disabled selected>선택하세요!</option>
									<option value = "01" >01</option>
									<option value = "02" >02</option>
									<option value = "03" >03</option>
									<option value = "04" >04</option>
									<option value = "05" >05</option>
									<option value = "06" >06</option>
									<option value = "07" >07</option>
									<option value = "08" >08</option>
									<option value = "09" >09</option>
									<option value = "10" >10</option>
									<option value = "11" >11</option>
									<option value = "12" >12</option>
									<option value = "13" >13</option>
									<option value = "14" >14</option>
									<option value = "15" >15</option>
									<option value = "16" >16</option>
									<option value = "17" >17</option>
									<option value = "18" >18</option>
									<option value = "19" >19</option>
									<option value = "20" >20</option>
									<option value = "21" >21</option>
									<option value = "22" >22</option>
									<option value = "23" >23</option>
									<option value = "24" >24</option>
									<option value = "25" >25</option>
									<option value = "26" >26</option>
									<option value = "27" >27</option>
									<option value = "28" >28</option>
									<option value = "29" >29</option>
									<option value = "30" >30</option>
									<option value = "31" >31</option>
								</select>일 
				        </div>                 
			       	</div>
			       	<div class="clear"></div>

			       	<div class="form email">
				        <div class="col1">이메일</div>
				        <div class="col2">
							<input type="text" name="email1">@
								<select name = "email2">
									<option value = "" disabled selected>선택하세요!</option>
									<option value = "ewhain.net" >ewhain.net</option>
									<option value = "gamil.com" >gamil.com</option>
									<option value = "naver.com" >naver.com</option>
								</select>
				        </div>                 
			       	</div>
			       	<div class="clear"></div>

			       	<div class="bottom_line"> </div>
			       	<div class="buttons">
	                	<img style="cursor:pointer" src="./img/button_save.gif" onclick="check_input()">&nbsp;
                  		<img id="reset_button" style="cursor:pointer" src="./img/button_reset.gif"
                  			onclick="reset_form()">
	           		</div>
           	</form>
        	</div> <!-- join_box -->
        </div> <!-- main_content -->
	</section> 
	<footer>
    	<?php include "footer.php";?>
    </footer>
</body>
</html>

