<?php

$root_dir    = "";
$pagesize    = 25;

$db          = "ddavis_db";
$db_user     = "ddavis20";
$db_password = "cmsunite";

$ldap_host   = "ldaps://isuad.indstate.edu/";
$ldap_port   = 636;
$ldap_basedn = "ou=ISU Users,dc=isuad,dc=indstate,dc=edu";

$myconn = new mysqli(NULL, $db_user, $db_password, $db);
if ($myconn->connect_error) {
   die ("Failed to connect to database (" . $myconn->connect_errono . "): " . $myconn->connect_error);
}
$myconn->query("SET NAMES 'utf8'"); 

$username = isset($_POST["user1"])? $conn->real_escape_string($_POST["user1"]) : null;
$password = isset($_POST["password1"])? $conn->real_escape_string($_POST["password1"]) : null;

function my_query($q)
{
  global $myconn;

  $res = $myconn->query($q) or die ("Error querying database: ($q) ". $myconn->error);
  return $res;
}

function safe_query($tbl, $safequery, $action)
{
  $l = "";
  if (gettype($tbl) == "array") {
    foreach($tbl as $t) {
      if (strlen($l) > 0) $l .= ", ";
      $l .= "`$t` $action";
    }
  } else if (gettype($tbl) == "string") $l = "`$tbl` $action";
  else die("safe_query: table specification not string or array of strings.\n");
  
  my_query("LOCK TABLES $l");
  $results = my_query($safequery);
  my_query("UNLOCK TABLES");
  
  return $results;
}


function my_escape($s)
{
  global $myconn;
  return $myconn->real_escape_string($s);
}

function ldap_auth($username, $password, $type)
{
  $ou = Array("EMP" => "ou=EMP,", "STU" => "ou=STU,", "FAC" => "ou=FAC,");
  global $ldap_host, $ldap_port, $ldap_basedn;
  if ($username == "") return null;

  $basedn = $ou[$type] . $ldap_basedn;
  $ldap = ldap_connect($ldap_host,$ldap_port);
  if ($ldap == FALSE){ 
     echo "could not connect to adap";
     return null;

  }
  ldap_set_option($ldap, LDAP_OPT_PROTOCOL_VERSION, 3);
  ldap_set_option($ldap, LDAP_OPT_REFERRALS, 0);

  if (ldap_bind($ldap, "cn=$username,$basedn", $password) === FALSE) {
    ldap_close($ldap);
    return null;
  };

  $result = ldap_search($ldap, $basedn, "cn=$username", array("cn", "mail", "givenname", "sn", "displayname", "memberof"));
  if ($result === FALSE) {
    ldap_close($ldap);
    return null;
  }
  $data = ldap_get_entries($ldap, $result);
  $ldata['count'] = $data['count'];
  if ($ldata['count'] == 0) return null;

  for($i=0; $i < $data['count']; $i++) {
    for ($j=0; $j< $data[$i]['count'];$j++){
      $indx = $data[$i][$j];
      if ($indx == "memberof") {
        $ldata[$indx] = $data[$i][$indx];
      } else $ldata[$indx] = $data[$i][$indx][0];
    }
  }

  ldap_close($ldap);
  return $ldata;
}

function error($message)
{
  echo "$message";
  die();
}
?>
