<?php
include "config.php";

$path=isset($_SERVER['QUERY_STRING'])? "?".$_SERVER['QUERY_STRING'] : "";

if (isset($_POST['username'])) {
  $username = isset($_POST['username'])? $_POST['username'] : error("Missing username");
  $password = isset($_POST['password'])? $_POST['password'] : error("Missing password");
  if($username == "Boss") $type = "EMP";
  else $type = "STU";
  //$res = ldap_auth($username, $password, $type);
  //if ($res == null) error("Authentication failed.");
  if(($username != "Boss" || $username != "Student") && $password != "work") error("Authentication failed."); 
  else {
    if($type == "EMP")
      header("Location: http://cs.indstate.edu/~ddavis20/questionmatic/backend.php");
    else
      header("Location: http://cs.indstate.edu/~ddavis20/questionmatic/questionmatic.php");
  }
}
?>
<!DOCTYPE html>
<html>
<head>
   <meta charset='ascii'>
   <link rel='stylesheet' href='css/b.css' type='text/css' />
   <title>User Authentication</title>
   <a href="https://drive.google.com/open?id=0B-4on2XkoLofbDFmaHgzVDFSRnc" class="a1">View Source Code</a>
</head>
<body>
  <form name = "add" action = "login.php" method = "POST">
    <table>
     <tr>
     <td>Username:</td>
     <td><input type="text" name="username"/> </td>
     </tr>
     <tr>
     <td>Password:</td>
     <td><input type="password" name="password"/> </td>
     </tr>
     <tr>
     <td><input type="Submit" value="Login"/> </td>
     </tr>
    </table>
  </form>
  <p> Students can only access the Quetionmatic webpage, so [Username]: "Student"</p>
     <p> Only the Boss has access to the Backend Webpage, so [Username]: "Boss"</p>
     <p> Both the Students and Boss share the same password, so [Passwork]: "work" </p>
</body>
</html>
