<?php
  if (isset($_COOKIE['quizomatic'])) {
    setcookie("quizomatic", $_COOKIE['quizomatic'], time()-3600);
  }
  header("Location: login.php");
?>
