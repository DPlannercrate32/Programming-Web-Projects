 <?php
  //include "config.php";
  $host = "localhost";
  $user = "ddavis20";
  $pass = "cmsunite";
  $dbname = "ddavis_db";

  $conn = new mysqli($host, $user, $pass, $dbname);
  if($conn->connect_error){
	die("Connection failed: " . $conn->connect_error);
  }

  $table1 = "CREATE TABLE IF NOT EXISTS user2 (
      id INT AUTO_INCREMENT PRIMARY KEY,
      name VARCHAR(50) NOT NULL,
      email VARCHAR(100),
      created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
  )";

  $table2 = "CREATE TABLE IF NOT EXISTS submission2 (
      id INT AUTO_INCREMENT PRIMARY KEY,
      user_id INT,
      submitted_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
      FOREIGN KEY (user_id) REFERENCES user2(id)
  )";

  $table3 = "CREATE TABLE IF NOT EXISTS response2 (
      id INT AUTO_INCREMENT PRIMARY KEY,
      submission_id INT,
      question VARCHAR(255),
      answer VARCHAR(255),
      FOREIGN KEY (submission_id) REFERENCES submission2(id)
  )";

  // Execute table creation
  // Execute table creation
  if ($conn->query($table1) === TRUE) {
      echo "Table 'user2' checked/created successfully.<br>";
  } else {
      echo "Error creating 'users': " . $conn->error . "<br>";
  }

  if ($conn->query($table2) === TRUE) {
      echo "Table 'submission2' checked/created successfully.<br>";
  } else {
      echo "Error creating 'posts': " . $conn->error . "<br>";
  }
  if ($conn->query($table3) === TRUE) {
      echo "Table 'response2' checked/created successfully.<br>";
  } else {
      echo "Error creating 'comments': " . $conn->error . "<br>";
  }

  //$time = getdate();
  
  $scenario = isset($_POST["scenario2"])? $_POST["scenario2"] : null;
  $nic_speed = isset($_POST["nic_speed"])? $_POST["nic_speed"] : null;
  $num_nics = isset($_POST["num_nics"])? $_POST["num_nics"] : null;
  $nic_type = isset($_POST["nic_type"])? $_POST["nic_type"] : null;
  $os = isset($_POST["os2"])? implode(", ", $_POST["os2"]) : null;
  $SMP = isset($_POST["SMP"])? $_POST["SMP"] : null;
  $network_type = isset($_POST["network_type2"])? implode(", ", $_POST["network_type2"]) : null;
  $bandwidth_info = isset($_POST["bandwidth_info"])? $_POST["bandwidth_info"] : null;
  $Expected = isset($_POST["Expected"])? $_POST["Expected"] : null;
  $Other_ER = isset($_POST["Other_ER"])? implode(", ", $_POST["Other_ER"]) : null;
 
 //User info

  $first_name = isset($_POST["first_name"])? $_POST["first_name"] : "";
  $last_name = isset($_POST["last_name"])? $_POST["last_name"] : "";
  $name = $first_name . $last_name;
  $email = isset($_POST["email"])? $_POST["email"] : "";

  //if ($Name == null || $Question == null || $Answer == null) {
    //error("Post missing data -- aborting.\n");
  //}


 
  $sql = "INSERT INTO user2 (name, email) VALUES (?, ?)";
  //$sql = "INSERT INTO submission (name, question, answer) VALUES (?, ?, ?)";
  /*$sql2 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql3 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql4 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql5 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql6 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql7 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql8 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql9 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql10 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";*/

  

  $stmt = $conn->prepare($sql);
  $stmt->bind_param("ss", $name, $email);
  if (!$stmt->execute()) {
      echo "Error inserting submission: " . $stmt->error;
      exit();
  }
  $user_id = $conn->insert_id;
  $stmt->close();

  $sql_submission = "INSERT INTO submission2 (user_id) VALUES (?)";
  $stmt = $conn->prepare($sql_submission);
  $stmt->bind_param("i", $user_id);
  if (!$stmt->execute()) {
      echo "Error inserting submission: " . $stmt->error;
      exit();
  }
$submission_id = $conn->insert_id;
$stmt->close();

$sql_response = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";
$stmt = $conn->prepare($sql_response);

$responses = [
    ["scenario", $scenario],
    ["nic_speed", $nic_speed],
    ["num_nics", $num_nics],
    ["nic_type", $nic_type],
    ["os", $os],
    ["SMP", $SMP],
    ["network_type", $network_type],
    ["bandwidth_info", $bandwidth_info],
    ["Expected", $Expected],
    ["Other_ER", $Other_ER],
];

foreach ($responses as $response) {
    
    $question = $response[0];
    $answer = isset($response[1]) ? $response[1] : "";
    $stmt->bind_param("iss", $submission_id, $question, $answer);
    if (!$stmt->execute()) {
        echo "Error: " . $stmt->error;
    }
    
}

echo "Data successfully inserted into the tables!";

$stmt->close();
$conn->close();

  /*$result2 = safe_query("QA2", "
    INSERT INTO QA2
      (`name`, `question`, `answer`)
    VALUES
      ('$Name', '$Question', '$Answer')", "WRITE");*///

  //sleep(2);
  //if($Submit)
   //header("Location: http://127.0.0.1/edsa-Questionmatic/login.php");
?>
