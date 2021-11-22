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
            즐겨찾기 목록 >  역
        </h3>
        <ul id="util_list">
                <li>
                    <span class="col1">역</span>
                    <span class="col2">혼잡도</span>

                </li>
   <?php
    $mysqli = mysqli_connect("localhost", "team16", "team16", "team16");
    if(mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }
    else {
        $sql = "SELECT sl.station_id as station_id, avg(sci.inline_congest) as inline_congest, avg(sci.outline_congest) as outline_congest
                FROM station_likes as sl, station_info as si, station_congest_info as sci
                WHERE (sl.station_id=si.station_id) and (si.station_id=sci.station_id)
                GROUP BY sl.station_id;";
        
        $res = mysqli_query($mysqli, $sql);
        
        if($res){
            while($congest = mysqli_fetch_array($res, MYSQLI_ASSOC)){
                $station_id = $congest['station_id'];
                $inline_congest = $congest['inline_congest'];
                $outline_congest = $congest['outline_congest'];
                $avg_congest = ($inline_congest+$outline_congest)/2;
            
                $sql_1 = "select station from station_info where station_id=" . $station_id . ";";
                $res_1 = mysqli_query($mysqli, $sql_1);
                    if ($res_1) {
                        $newArray = mysqli_fetch_array($res_1, MYSQLI_ASSOC);
                        $station = $newArray['station'];
                    }
                mysqli_free_result($res_1);
        ?>
        <li>
            <span class="col1"><?=$station?></span>
            <span class="col2"><?=$avg_congest?>%</span>
        </li>
    <?php
       }
        }
        else{
            printf("could not retrieve records\n"); //: %s\n", mysqli_error($mysqli));
        }
        mysqli_free_result($res);

        ///////////////////////////////////////////////////////////////////////////////////////////
        mysqli_close($mysqli);
    }
    
?>
        <span class="col2"></span>
    </ul>
</div>  




</section>
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>


