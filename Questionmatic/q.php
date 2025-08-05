 <?php
  include "config.php";

  //$time = getdate();

  $Name = isset($_POST["name"])? my_escape($_POST["name"]) : null;
  $Question = isset($_POST["q"])? my_escape($_POST["q"]) : null;
  $Answer = isset($_POST["a"])? my_escape($_POST["a"]) : null;
  //$Submit = $_POST["sub"];


  if ($Name == null || $Question == null || $Answer == null) {
    error("Post missing data -- aborting.\n");
  }

  $result2 = safe_query("QA", "
    INSERT INTO QA
      (`name`, `question`, `answer`)
    VALUES
      ('$Name', '$Question', '$Answer')", "WRITE");

  sleep(2);
  //if($Submit)
   header("Location: http://cs.indstate.edu/~ddavis20/questionmatic/login.php");
?>
