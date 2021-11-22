        <div id="main_img_bar">
            <img src="./img/main_logo2.png">
        </div>
        <div id="main_content">
            <div id="latest">
                <h4>최근 신고 게시글</h4>
                <ul>
<!-- 최근 신고 게시 글 DB에서 불러오기 -->
<?php
    $con = mysqli_connect("localhost", "team16", "team16", "team16");
    $sql = "select * from board order by id desc limit 5";
    $result = mysqli_query($con, $sql);

    if (!$result)
        echo "신고 게시판 DB 테이블(board)이 생성 전이거나 아직 게시글이 없습니다!";
    else
    {
        while( $row = mysqli_fetch_array($result) )
        {
            $regist_day = substr($row["regist_day"], 0, 10);
?>
                <li>
                    <span> <?=$row["station"]?>역 </span>
                    <span><?=$row["userid"]?></span>
                    <span><?=$regist_day?></span>
                </li>
<?php
        }
    }
?>
            </div>
            <div id="rank">
                <h4>임산부석 시간대별 이용률 랭킹</h4>
               
                <ul>
                
                

<!-- 포인트 랭킹 표시하기 -->
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

        //4-1. 시간대별로 배려석 이용률 높은 순 랭킹
        
        $sql4_1 = "SELECT use_hour, avg(util) as avg_util,
                rank() over (order by avg_util desc) as rank_avg_util
                FROM v_utilization
                GROUP BY use_hour
                ORDER BY rank_avg_util LIMIT 5;";
        $res4_1 = mysqli_query($mysqli, $sql4_1);
        if($res4_1){
            while($priorIncrease = mysqli_fetch_array($res4_1, MYSQLI_ASSOC)){
                $rank_avg_util = $priorIncrease['rank_avg_util'];
                $use_hour = $priorIncrease['use_hour'];
                $avg_util = $priorIncrease['avg_util']*100;
?>
                <li>
                    <span>랭킹<?=$rank_avg_util?></span>
                    <span><?=$use_hour?></span>
                    <span><?=$avg_util?>%</span>
                </li>
<?php
             }
        }
        else{
            echo 'could not retrieve records</br>'; //: %s\n", mysqli_error($mysqli));
        }
        mysqli_free_result($res4_1);
        mysqli_close($mysqli);
    }
?>
                </ul>
            </div>
        </div>