 <?php
  
  $host = "localhost";
  $username = 'root'; // Use your MySQL admin user
  $password = '';     // Use your MySQL admin password
  $connection = new mysqli($host, $username, $password);

  if ($connection->connect_error) {
      die("Connection failed: " . $connection->connect_error);
  }


  $newDb = "ddavis_db2";
  $newUser = "ddavis32";
  $newUserPass = "cmsunite";  

  // Create the database
  $sqlCreateDb = "CREATE DATABASE IF NOT EXISTS `$newDb`";
  if ($connection->query($sqlCreateDb) === TRUE) {
      echo "Database '$newDb' created or already exists.<br>";
  } else {
      echo "Error creating database: " . $connection->error . "<br>";
  }

  // Create the user
  $sqlCreateUser = "CREATE USER IF NOT EXISTS '$newUser'@'localhost' IDENTIFIED BY '$newUserPass'";
  if ($connection->query($sqlCreateUser) === TRUE) {
      echo "User '$newUser' created or already exists.<br>";
  } else {
      echo "Error creating user: " . $connection->error . "<br>";
  }

  // Grant privileges
  $sqlGrant = "GRANT ALL PRIVILEGES ON `$newDb`.* TO '$newUser'@'localhost'";
  if ($connection->query($sqlGrant) === TRUE) {
      echo "Privileges granted to '$newUser' on '$newDb'.<br>";
  } else {
      echo "Error granting privileges: " . $connection->error . "<br>";
  }

  // Apply privileges immediately
  $connection->query("FLUSH PRIVILEGES"); 

  $connection->close();
  

  $user = "ddavis32";
  $pass = "cmsunite";
  $dbname = "ddavis_db2";

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
  
  $scenario = isset($_POST["scenario"])? $_POST["scenario"] : null;
  $gpu_type = isset($_POST["gpu_type"])? $_POST["gpu_type"] : null;
  $num_gpus = isset($_POST["num_gpus"])? $_POST["num_gpus"] : null;
  $cpu_type = isset($_POST["cpu_type"])? $_POST["cpu_type"] : null;
  $os = isset($_POST["os"])? implode(", ", $_POST["os"]) : null;
  $network_type = isset($_POST["network_type"])? implode(", ", $_POST["network_type"]) : null;
  $bandwidth = isset($_POST["bandwidth"])? implode(", ", $_POST["bandwidth"]) : null;
  $num_servers = isset($_POST["num_servers"])? $_POST["num_servers"] : null;
  $other_requirements = isset($_POST["other_requirements"])? $_POST["other_requirements"] : null;

  //User info

  $first_name = isset($_POST["first_name"])? $_POST["first_name"] : "";
  $last_name = isset($_POST["last_name"])? $_POST["last_name"] : "";
  $name = $first_name . " " . $last_name;
  $email = isset($_POST["email"])? $_POST["email"] : "";

  //if ($Name == null || $Question == null || $Answer == null) {
    //error("Post missing data -- aborting.\n");
  //}


 
  $sql = "INSERT INTO user2 (name, email) VALUES (?, ?)";
  //$sql = "INSERT INTO submission (name, question, answer) VALUES (?, ?, ?)";
  /*$sql2 = "INSERT INTO response (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql3 = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql4 = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql5 = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql6 = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql7 = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql8 = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql9 = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";
  $sql10 = "INSERT INTO response2 (submission_id, question, answer) VALUES (?, ?, ?)";*/

  

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
    ["gpu_type", $gpu_type],
    ["num_gpus", $num_gpus],
    ["cpu_type", $cpu_type],
    ["os", $os],
    ["network_type", $network_type],
    ["bandwidth", $bandwidth],
    ["num_servers", $num_servers],
    ["other_requirements", $other_requirements],
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
echo "Variable: " . $other_requirements;
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
