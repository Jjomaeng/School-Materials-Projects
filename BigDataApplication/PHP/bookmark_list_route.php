<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>BADGE</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/util.css">
</head>
<body> 
<header>
    <?php include "header.php";?>
</header> 
<section>
	<div id="main_img_bar">
        <img src="./img/main_logo2.png">
    </div>

    <div id="util_box">
        <h3>
            즐겨찾기 목록 > 경로
        </h3>
        <ul id="util_list">
                <li>
                    <span class="col1">출발역</span>
                    <span class="col2">도착역</span>
                    <span class="col3">이용시간대</span>
                    <span class="col4">혼잡도</span>
                </li>
        <?php
        $mysqli = mysqli_connect("localhost","team16","team16","team16");
        if(mysqli_connect_errno()){
          printf("Connect failed: %s\n", mysqli_connect_error());
          exit();
        }else{
          $sql="Select id,user_id,dt.departure_id,dt.destination_id,departure_station,station as destination_station,use_time, congest_name from (SELECT * FROM `bookmarks` as bm
          inner join station_info as s
          on bm.destination_id=s.station_id
          where user_id='".$userid."') as dt
          inner join (SELECT departure_id,station as departure_station FROM `bookmarks`as b 
          inner join station_info as si 
          on b.departure_id=si.station_id
          where user_id='".$userid."') as dp
          on dt.departure_id= dp.departure_id
          ;";
          $res = mysqli_query($mysqli,$sql);
          if($res){
            while ($newArray = mysqli_fetch_array($res, MYSQLI_ASSOC)) {
              $departure_station = $newArray['departure_station'];
              $destination_station = $newArray['destination_station'];
              $use_time = $newArray['use_time'];
              $congest_name = $newArray['congest_name'];
              ?>
              <li>
              <span class="col1"> <?= $departure_station ?> </span>
              <span class="col2"> <?= $destination_station ?> </span>
              <span class="col3"> <?= $use_time ?> </span>
              <span class="col4"> <?= $congest_name ?> </span>
            </li>
            <?php
            }
          }else{
            printf("Could not load data: %s\n",mysqli_error($mysqli));
          }
        mysqli_close($mysqli);
        }
        ?>
        <li></li>
        </ul>
    </div>
</section>
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>