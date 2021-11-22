<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>BADGE</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/board.css">
<script>
  function check_input() {
      if (!document.congestion_form.departure_id.value)
      {
          alert("출발역을 선택하세요!");
          document.congestion_form.departure_id.focus();
          return;
      }
      if (!document.congestion_form.destination_id.value)
      {
          alert("도착역을 선택하세요!");
          document.congestion_form.destination_id.focus();
          return;
      }
      
      document.congestion_form.submit();
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
	    		혼잡도 검색 > 구역 선택 
		</h3>
	    <form  name="congestion_form" method="post" action="congestion_insert.php" enctype="multipart/form-data">
	    	 <ul id="board_form">

	    		<li>
	    			<span class="col1">출발역 : </span>
	    			<span class="col2"><select name = "departure_id">
									<option value = "" disabled selected>선택하세요</option>
				          <option value="201">시청</option>
				          <option value="202">을지로입구</option>
				          <option value="203">을지로3가</option>
				          <option value="204">을지로4가</option>
				          <option value="205">동대문역사문화공원</option>
				          <option value="206">신당</option>
				          <option value="207">상왕십리</option>
				          <option value="208">왕십리</option>
				          <option value="209">한양대</option>
				          <option value="210">뚝섬</option>
				          <option value="211">성수</option>
				          <option value="212">건대입구</option>
				          <option value="213">구의</option>
				          <option value="214">강변</option>
				          <option value="215">잠실나루</option>
				          <option value="216">잠실</option>
				          <option value="217">신천</option>
				          <option value="218">종합운동장</option>
				          <option value="219">삼성</option>
				          <option value="220">선릉</option>
				          <option value="221">역삼</option>
				          <option value="222">강남</option>
				          <option value="223">교대</option>
				          <option value="224">서초</option>
				          <option value="225">방배</option>
				          <option value="226">사당</option>
				          <option value="227">낙성대</option>
				          <option value="228">서울대입구</option>
				          <option value="229">봉천</option>
				          <option value="230">신림</option>
				          <option value="231">신대방</option>
				          <option value="232">구로디지털단지</option>
				          <option value="233">대림</option>
				          <option value="234">신도림</option>
				          <option value="235">문래</option>
				          <option value="236">영등포구청</option>
				          <option value="237">당산</option>
				          <option value="238">합정</option>
				          <option value="239">홍대입구</option>
				          <option value="240">신촌</option>
				          <option value="241">이대</option>
				          <option value="242">아현</option>
				          <option value="243">충정로</option>
				        </select>
							</span>
	    		</li>


	    		<li>
	    			<span class="col1">도착역 : </span>
	    			<span class="col2"><select name = "destination_id">
									<option value = "" disabled selected>선택하세요</option>
				          <option value="201">시청</option>
				          <option value="202">을지로입구</option>
				          <option value="203">을지로3가</option>
				          <option value="204">을지로4가</option>
				          <option value="205">동대문역사문화공원</option>
				          <option value="206">신당</option>
				          <option value="207">상왕십리</option>
				          <option value="208">왕십리</option>
				          <option value="209">한양대</option>
				          <option value="210">뚝섬</option>
				          <option value="211">성수</option>
				          <option value="212">건대입구</option>
				          <option value="213">구의</option>
				          <option value="214">강변</option>
				          <option value="215">잠실나루</option>
				          <option value="216">잠실</option>
				          <option value="217">신천</option>
				          <option value="218">종합운동장</option>
				          <option value="219">삼성</option>
				          <option value="220">선릉</option>
				          <option value="221">역삼</option>
				          <option value="222">강남</option>
				          <option value="223">교대</option>
				          <option value="224">서초</option>
				          <option value="225">방배</option>
				          <option value="226">사당</option>
				          <option value="227">낙성대</option>
				          <option value="228">서울대입구</option>
				          <option value="229">봉천</option>
				          <option value="230">신림</option>
				          <option value="231">신대방</option>
				          <option value="232">구로디지털단지</option>
				          <option value="233">대림</option>
				          <option value="234">신도림</option>
				          <option value="235">문래</option>
				          <option value="236">영등포구청</option>
				          <option value="237">당산</option>
				          <option value="238">합정</option>
				          <option value="239">홍대입구</option>
				          <option value="240">신촌</option>
				          <option value="241">이대</option>
				          <option value="242">아현</option>
				          <option value="243">충정로</option>
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
