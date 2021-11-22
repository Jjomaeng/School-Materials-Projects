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
<
<section>
    <div id="util_box">
        <h3>
            배려석 증설 좌석수
        </h3>
        <ul id="util_list">
                <li>
                    <span class="col1">이용 시간</span>
                    <span class="col2">필요한 좌석 수</span>
                </li>

    <?php
    $mysqli = mysqli_connect("localhost", "team16", "team16", "team16");
    if(mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }
    else {

        //1. 배려석 이용률 구하기
        $sql1 = "CREATE OR REPLACE VIEW v_utilization AS
        SELECT L.name as line_name, (new_ui.sitCnt/L.pregnant_seat/L.car_number/L.run_train) as util, (new_ui.preCnt/L.pregnant_seat/L.car_number/L.run_train) as ratio, new_ui.use_hour as use_hour
        FROM line2_info as L, 
           (SELECT line_name, use_hour, SUM(sit) as sitCnt, SUM(pregnant) as preCnt
            FROM user_input as ui
            WHERE pregnant=1
            GROUP BY line_name, use_hour) as new_ui
        WHERE (L.name = new_ui.line_name);";
        
        $res1 = mysqli_query($mysqli, $sql1);
        
        if($res1!=TRUE){
            echo 'Could not create view v_tilization</br>'; //: %s\n",mysqli_error($mysqli));
        }

        ///////////////////////////////////////////////////////////////////////////////////////////
        
        mysqli_autocommit($mysqli, FALSE); //auto commit 끄기

        //2-1. 임산부-증설 테이블 초기화 & 임산부-증설 테이블에 이용률 넣고 배려석 증설 테이블의 기준치와 비교하기
        $sql2_1 = "TRUNCATE priority_increase;";
        
        $res2_1 = mysqli_query($mysqli, $sql2_1);
        
        $sql2_1 = "INSERT INTO priority_increase(line_name, use_hour, increase_standard_id)
        (SELECT ut.line_name, ut.use_hour, istd.id
        FROM v_utilization as ut, increase_standard as istd
        WHERE round(ut.ratio,1)=istd.utility_standard)
        ON DUPLICATE KEY UPDATE line_name = ut.line_name, use_hour = ut.use_hour, increase_standard_id = istd.id;";
        
        $res2_1 = mysqli_query($mysqli, $sql2_1);
        
        if($res2_1!=TRUE){
            mysqli_rollback($mysqli); //에러 발생 시 rollback
            echo 'Could not insert record to seatIncr</br>'; //: %s\n",mysqli_error($mysqli));
        }
        mysqli_commit($mysqli); //한 번에 commit
        mysqli_autocommit($mysqli, TRUE); //auto commit 다시 켜기

        ///////////////////////////////////////////////////////////////////////////////////////////

        //2-2. 배려석 증설 좌석수 구하기

        $sql2_2 = "SELECT pi.line_name as line_name, pi.use_hour as use_hour, istd.increase_number as increase_number
                    FROM priority_increase as pi, increase_standard as istd
                    WHERE pi.increase_standard_id=istd.id;";
        $res2_2 = mysqli_query($mysqli, $sql2_2);
        if($res2_2){
            while($priorIncrease = mysqli_fetch_array($res2_2, MYSQLI_ASSOC)){
                $line_name = $priorIncrease['line_name'];
                $use_hour = $priorIncrease['use_hour'];
                $increaseNum = $priorIncrease['increase_number'];
        ?>

        <li>
            <span class="col1"><?=$use_hour?></span>
            <span class="col2"><?=$increaseNum?></span>
        </li> 


        <?php
                  }
            }
            else{
                    echo 'could not retrieve records</br>'; //: %s\n", mysqli_error($mysqli));
            }
            mysqli_free_result($res2_2);
        ?>

    </ul>
</div>  

    <div id="util_box">
        <h3>
            시간대별 배려석 이용률
        </h3>
        <ul id="util_list">
                <li>
                    <span class="col1">시간대</span>
                    <span class="col2">이용률</span>
                </li>





    <?php
        $sql3_1 = "SELECT avg(util) as avg_util, use_hour
                FROM v_utilization
                GROUP BY use_hour ORDER BY use_hour;";
        $res3_1 = mysqli_query($mysqli, $sql3_1);
        if($res3_1){
            while($priorIncrease = mysqli_fetch_array($res3_1, MYSQLI_ASSOC)){
                $avg_util = $priorIncrease['avg_util']*100;
                $use_hour = $priorIncrease['use_hour'];

    ?>

        <li>
            <span class="col1"><?=$use_hour?></span>
            <span class="col2"><?=$avg_util?>%</span>
        </li> 


    <?php
                 }
            }
            else{
                echo 'could not retrieve records</br>'; //: %s\n", mysqli_error($mysqli));
            }
            mysqli_free_result($res3_1);
    ?>
    </ul>
</div>  

    <div id="util_box">
        <h3>
            TOTAL 배려석 이용률
        </h3>
        <ul id="util_list">
                <li>
                    <span class="col1">호선</span>
                    <span class="col2">이용률</span>
                </li>
<?php
        //3-2. 호선별로 배려석 이용률 통계

        $sql3_2 = "SELECT line_name, round(avg(util),4) as avg_util
                FROM v_utilization
                GROUP BY line_name ORDER BY line_name;";
        $res3_2 = mysqli_query($mysqli, $sql3_2);
        if($res3_2){
            while($priorIncrease = mysqli_fetch_array($res3_2, MYSQLI_ASSOC)){
                $line_name = $priorIncrease['line_name'];
                $avg_util = $priorIncrease['avg_util']*100;
?>

        <li>
            <span class="col1"><?=$line_name?></span>
            <span class="col2"><?=$avg_util?>%</span>
        </li> 


    <?php
         }
            }
            else{
                printf("could not retrieve records\n"); //: %s\n", mysqli_error($mysqli));
            }
            mysqli_free_result($res3_2);
        mysqli_close($mysqli);
    }
        
    ?>
    <span class="col2"></span>
    </ul>
</div>  


<li></li>

</section>
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>