<?php
include "config.php";

$pagesize=10;
$limit=$pagesize+1;

if (isset($_GET['page'])) $page=(int)$_GET['page'];
else $page=0;
$start = $page*3;

$url="";
$where="";


if (strlen($where) > 0) $where = " WHERE $where";

$res = safe_query("QA",
  "SELECT id, name, question, answer FROM QA $where ORDER BY id DESC LIMIT $start,$limit", "READ");
$rows = $res->num_rows;
?>


<!DOCTYPE html>

<html>
<head>
<title> Backend Page </title>
<link rel='stylesheet' href='css/a.css' type='text/css' />
</head>
<body>
<form method='get'>
<table>
 <tr>
 <td rowspan=2 style='width: 72%;'> <h1 class='header'>QA Table</h1></td>
 </tr>
</table>
</form>
<br>
<ol class='user'>
 <?php
  if ($res !== FALSE) {
    for($i=0; (($row_data = $res->fetch_assoc()) !== NULL) && $i < $pagesize; $i++) {
      $id = $row_data['id'];
      $name = $row_data['name'];
      $question = $row_data['question'];
      $answer = $row_data['answer'];
  ?>
 <li>
  <table>
   <tr><td class="data1" rowspan=2>
    <?php
      echo $name . "<br>";
    ?>
    </td>
    <td class="data2"> <?php echo "$question"; ?></td>
   </tr>
   <tr><td class="data3"><?php echo "$answer"; ?></td></tr> 
  </table>
 </li>
<?php
   }
 }
?>
 <li>
<?php
 if ($page > 0) {
   $pp=$page-1;
   echo "<a href='?page=$pp&$url'><button type='button'> Prev </button></a>";
 }
 if ($rows > $pagesize) {
   $pp=$page+1;
   echo "<a href='?page=$pp&$url' style='float: right;'><button type='button'> Next </button></a>";
 }
 echo "<div style='clear:both;'></div>";
?>
</ol>
</body>
</html> 
