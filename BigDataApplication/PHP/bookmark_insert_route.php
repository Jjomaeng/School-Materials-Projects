bo<meta charset="utf-8">
<?php
session_start();
if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
else $userid = "";
if (isset($_SESSION["username"])) $username = $_SESSION["username"];
else $username = "";
$mysqli = mysqli_connect("localhost", "team16", "team16", "team16");
if (mysqli_connect_errno()) {
  printf("Connect failed: %s\n", mysqli_connect_error());
  exit();
} else {
  $departure_id = $_POST['departure_id'];
  $destination_id = $_POST['destination_id'];
  $use_time = $_POST['use_time'];
  /** 출발역 */
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
  if ($departure_id < $destination_id) {
    $sql_4 = "select use_time,avg(inline_congest) as average
        from station_info st 
        inner join station_congest_info sc on st.station_id = sc.station_id 
        where (st.station_id BETWEEN " . $departure_id . " and " . $destination_id . ") and (use_time='". $use_time . "');";
  } else {
    $sql_4 = "select use_time,avg(outline_congest) as average
        from station_info st 
        inner join station_congest_info sc on st.station_id = sc.station_id 
        where (st.station_id BETWEEN " . $destination_id . " and " . $departure_id . ") and (use_time='" . $use_time . "');";
  }
  $res_4 = mysqli_query($mysqli, $sql_4);
  $congestion_name = "";
  if ($res_4) {
    $result = mysqli_fetch_array($res_4, MYSQLI_ASSOC);
    $avg = $result['average'];
    $min = 0;
    foreach ($congest as $x => $x_value) {
      if ($min < $avg && $avg <= $x_value) {
        $congestion_name = $x;
        break;
      } else if ($avg > $x_value) {
        $min = $x_value;
      }
    }
  }
  /** 데이터 추가 */

  $sql_5 = "Insert into bookmarks (user_id,departure_id,destination_id,use_time,congest_name) values
            ('" . $userid . "'," . $departure_id . "," . $destination_id . ",'" . $use_time . "','" . $congestion_name . "');";
  $res_5 = mysqli_query($mysqli, $sql_5) or die(mysqli_error($mysqli));;
  if ($res_5 === True) {
    echo "Data successfully was inserted into Bookmarks table";
  } else {
    printf("Could not insert data: %s\n", mysqli_error($mysqli));
  }
  mysqli_close($mysqli);

  echo "
       <script>
        location.href = 'bookmark_list_route.php';
       </script>
    ";
}
?>