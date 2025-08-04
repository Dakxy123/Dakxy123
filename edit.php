<?php
require_once 'db_connect.php';
require_once 'PatientManager.php';

$patientManager = new PatientManager($conn);

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $id = $_POST['id'];
    $name = $_POST['name'];
    $age = $_POST['age'];
    $contact = $_POST['contact'];
    $medicalHistory = $_POST['medical_history'];
    $currentCondition = $_POST['current_condition'];

    $patientManager->updatePatient($id, $name, $age, $contact, $medicalHistory, $currentCondition);
    header("Location: index.php");
}

$id = $_GET['id'];
$query = "SELECT * FROM patients WHERE id = $id";
$result = mysqli_query($conn, $query);
$patient = mysqli_fetch_assoc($result);
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Edit Patient</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <h1>Edit Patient</h1>
        <form action="edit.php" method="POST">
            <input type="hidden" name="id" value="<?php echo $patient['id']; ?>">
            <label for="name">Name:</label>
            <input type="text" id="name" name="name" value="<?php echo $patient['name']; ?>" required>
            <label for="age">Age:</label>
            <input type="number" id="age" name="age" value="<?php echo $patient['age']; ?>" required>
            <label for="contact">Contact:</label>
            <input type="text" id="contact" name="contact" value="<?php echo $patient['contact']; ?>" required>
            <label for="medical_history">Medical History:</label>
            <textarea id="medical_history" name="medical_history" rows="3" required><?php echo $patient['medical_history']; ?></textarea>
            <label for="current_condition">Current Condition:</label>
            <textarea id="current_condition" name="current_condition" rows="3" required><?php echo $patient['current_condition']; ?></textarea>
            <button type="submit">Update Patient</button>
        </form>
    </div>
</body>
</html>