<!DOCTYPE html>

<head>
  <header>
    <?php include "header.php";?>
  </header> 
  <head>
    <meta charset="utf-8">
    <title>BADGE</title>
    <link rel="stylesheet" type="text/css" href="./css/common.css">
    <link rel="stylesheet" type="text/css" href="./css/util.css">
  </head>

<body>

  <section>

    <div id="util_box">
      <h3 id="util_title">
        
        <?php
        $mysqli = mysqli_connect("localhost", "team16", "team16", "team16");
        if (mysqli_connect_errno()) {
          printf("Connect failed: %s\n", mysqli_connect_error());
          exit();
        } 
        else {
          /** 출발역 */
          $departure_id = $_POST['departure_id'];
          $destination_id = $_POST['destination_id'];
          $sql_1 = "select station from station_info where station_id=" . $departure_id . ";";
          $res_1 = mysqli_query($mysqli, $sql_1);
          if ($res_1) {
            $newArray = mysqli_fetch_array($res_1, MYSQLI_ASSOC);
            $departure = $newArray['station'];
          }
          mysqli_free_result($res_1);

          /** 도착역 */
          $sql_2 = "select station from station_info where station_id=" . $destination_id . ";";
          $res_2 = mysqli_query($mysqli, $sql_2);
          if ($res_2) {
            $newArray = mysqli_fetch_array($res_2, MYSQLI_ASSOC);
            $destination = $newArray['station'];
          }
          mysqli_free_result($res_2);
        ?>
          <?= $departure ?> > <?= $destination ?>
      </h3>
      <ul id="util_list">
        <li>
          <span class="col1">시간대</span>
          <span class="col1"> 평균 혼잡도 </span>
          <span class="col2"> 예상 혼잡도 </span>
        </li>
        <?php
          /** 혼잡도 */
          $congest = array();
          $sql_3 = "select * from congestions";
          $res_3 = mysqli_query($mysqli, $sql_3);

          if ($res_3) {
            while ($newArray = mysqli_fetch_array($res_3, MYSQLI_ASSOC)) {
              $key = $newArray['name'];
              $value = $newArray['congestion_level'];
              $congest[$key] = $value;
            }
          }
          asort($congest);
          mysqli_free_result($res_3);

          /** 내/외선 시간대별 혼잡도 구간 평균 구하기 */
          $station_congestion = array();
          if ($departure_id < $destination_id) {
            $sql_4 = "select use_time,avg(inline_congest) as average
        from station_info st 
        inner join station_congest_info sc on st.station_id = sc.station_id 
        where st.station_id BETWEEN " . $departure_id . " and " . $destination_id . " group by use_time;";
          } else {
            $sql_4 = "select use_time,avg(outline_congest) as average
        from station_info st 
        inner join station_congest_info sc on st.station_id = sc.station_id 
        where st.station_id BETWEEN " . $destination_id . " and " . $departure_id . " group by use_time;";
          }
          $res_4 = mysqli_query($mysqli, $sql_4);
          if ($res_4) {
            while ($newArray = mysqli_fetch_array($res_4, MYSQLI_ASSOC)) {
              $time = $newArray['use_time'];
              $avg = $newArray['average'];
              $min = 0;
              $congestion_name = "";
              foreach ($congest as $x => $x_value) {
                if ($min < $avg && $avg <= $x_value) {
                  $congestion_name = $x;
                  break;
                } else if ($avg > $x_value) {
                  $min = $x_value;
                }
              }
              $s_c = array(
                'congestion_name' => $congestion_name,
                'time' => $time
              );
              array_push($station_congestion, $s_c);
        ?>
            <li>
              <span class="col1"> <?= $time ?> </span>
              <span class="col2"> <?= round($avg) ?> </span>
              <span class="col2"> <?= $congestion_name ?> </span>
            </li>
     

<?php
            }
          }
          mysqli_free_result($res_4);

          /** station_and_congest 초기화 */
          $sql_5 = "TRUNCATE station_and_congest;";
          $res_5 = mysqli_query($mysqli, $sql_5);

          /** 데이터 추가 */
          foreach ($station_congestion as $v) {
            $cn = $v['congestion_name'];
            $tm = $v['time'];
            $sql_6 = "Insert into station_and_congest (congestion_name,departure_id,destination_id,time) values
            ('" . $cn . "'," . $departure_id . "," . $destination_id . ",'" . $tm . "');";
            $res_6 = mysqli_query($mysqli, $sql_6) or die(mysqli_error($mysqli));;
          }

          mysqli_close($mysqli);
        }
?>
 </ul>
<br>
<br>
    </div> <!-- board_box -->
  </section>
  <footer>
    <?php include "footer.php"; ?>
  </footer>
</body>

</html>