<?php
//echo " server\n";
//var_dump($_SERVER);
//echo " get\n";
//var_dump($_GET);
//echo " post\n";
//var_dump($_POST);
//echo " request\r\n";
//var_dump($_REQUEST);
//echo " files\r\n";
//var_dump($_FILES);
//echo " globals\n";
//var_dump($GLOBALS);

echo getenv('GLOBALS');
foreach (getenv() as $key => $value) {
    echo $key . ' - ' . $value . "\n";
}
?>