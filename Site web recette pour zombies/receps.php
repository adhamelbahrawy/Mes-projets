<?php include "sql.php" ?>
<?php include "Back/Redondances/head.php" ?>
<body>
    <div class="wrapper">
        <?php
        $rows = $pdo->query("SELECT * FROM recep ORDER BY id ASC")->fetchAll();
        foreach($rows as $row){ ?>
            <div class="row">
                <h1 class="dispRecepName"><?php echo $row["recep_name"]?></h1>
                <h2 class="dispName">By <?php echo $row["first_name"]." ".$row["last_name"]?></h2>
                <div class="dispRecep"><?php echo $row["recepie"]?></div>
            </div>
        <?php } ?>
    </div>
    <?php include "Back/Redondances/footer.php" ?>
</body>
</html>