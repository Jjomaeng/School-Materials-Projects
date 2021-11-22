<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8">
  <title>BEDGE</title>
  <link rel="stylesheet" type="text/css" href="./css/common.css">
  <link rel="stylesheet" type="text/css" href="./css/board.css">

  <script type="text/javascript">
    function check_input(num) {
      if (num == 1) {
        if (!document.bookmark_form_route.departure.value) {
          alert("출발역을 입력하세요!");
          document.bookmark_form_route.departure.focus();
          return;
        }
        if (!document.bookmark_form_route.destination.value) {
          alert("도착역을 입력하세요!");
          document.bookmark_form_route.destination.focus();
          return;
        }
        document.bookmark_form_route.submit();
      } else if (num == 2) {
        if (!document.bookmark_form_station.station.value) {
          alert("지하철역을 입력하세요!");
          document.bookmark_form_station.station.focus();
          return;
        }
        document.bookmark_form_station.submit();
      }

    }
  </script>
</head>

<body>
  <header>
    <?php include "header.php"; ?>
  </header>
  <?php
  if (!$userid) {
    echo ("<script>
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
        즐겨찾기 입력 > 경로
      </h3>
      <form name="bookmark_form_route" method="post" action="bookmark_insert_route.php" enctype="multipart/form-data">
        <ul id="board_form">
          <li>
            <span class="col1">이름 : </span>
            <span class="col2"><?= $userid ?></span>
          </li>
          <li>
            <span class="col1">출발역 : </span>
            <span class="col2">
              <select name="departure_id" id="departure_id" required>
                <option value="" disabled selected>출발역</option>
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
            <span class="col2">
              <select name="destination_id" id="destination_id" required>
                <option value="" disabled selected>도착역</option>
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
            <span class="col1">이용시간대 : </span>
            <span class="col2">
              <select name="use_time" id="use_time" required>
                <option value="" disabled selected>이용 시간</option>
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

        </ul>
        <ul class="buttons">
          <li><button type="submit" name="submit_btn1" id="submit_btn1">완료</button></li>
          <li><button type="button" onclick="location.href='bookmark_list_route.php'">목록</button></li>
        </ul>
      </form>
    </div> <!-- board_box -->

    <div id="board_box">
      <h3 id="board_title">
        즐겨찾기 입력 > 역
      </h3>
      <form name="bookmark_form_station" method="post" action="bookmark_insert_station.php" enctype="multipart/form-data">
        <ul id="board_form">

          <li>
            <span class="col1">이름 : </span>
            <span class="col2"><?= $userid ?></span>
          </li>

          <li>
            <span class="col1">지하철역 : </span>
            <span class="col2"><select name="station_id" id="station_id" required>
                <option value="" disabled selected>선택하세요</option>
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
          <li><button type="submit" name="submit_btn2" id="submit_btn2">완료</button></li>
          <li><button type="button" onclick="location.href='bookmark_list_station.php'">목록</button></li>
        </ul>
      </form>
    </div> <!-- bookmark_box -->
  </section>

  <footer>
    <?php include "footer.php"; ?>
  </footer>
</body>

</html>