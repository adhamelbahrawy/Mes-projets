<?php
$recepName = htmlspecialchars($_POST["recepname"]);
$first = htmlspecialchars($_POST["first"]);
$last = htmlspecialchars($_POST["last"]);
$recep = htmlspecialchars($_POST["recep"]);

try
{
    $pdo = new PDO("sqlite:".dirname(__FILE__)."/recep.db");
    $pdo->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $pdo->query(
        "CREATE TABLE IF NOT EXISTS recep
            (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                recep_name VARCHAR(50) NOT NULL,
                first_name VARCHAR(50) NOT NULL,
                last_name VARCHAR(50) NOT NULL,
                recepie TEXT NOT NULL
            )"
        );

    if(
        preg_match("/^([a-zàâçéèêëîïôûùüÿñæœ0-9-]+ )*[a-zàâçéèêëîïôûùüÿñæœ0-9-]{1,50}$/i", $recepName)
        && preg_match("/^[\S]{1,50}$/", $first)
        && preg_match("/^[\S]{1,50}$/", $last)
        && $recep != ""
    )
    {
        $statement = $pdo->prepare(
            "INSERT INTO recep (recep_name, first_name, last_name, recepie) VALUES (:recep_name, :first_name, :last_name, :recepie)"
        );
        $statement->bindValue("recep_name", $recepName);
        $statement->bindValue("first_name", $first);
        $statement->bindValue("last_name", $last);
        $statement->bindValue("recepie", $recep);
        $statement->execute();
    }
}
catch(PDOException $exception)
{
    var_dump($exception);
}
?>