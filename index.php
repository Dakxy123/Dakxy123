<?php
require_once 'db_connect.php';
require_once 'PatientManager.php';

$patientManager = new PatientManager($conn);
$patients = $patientManager->getPatients();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Patients Record</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <h1>Patients Record</h1>
        <form action="create.php" method="POST" class="add-patient-form">
            <h2>Add New Patient</h2>
            <label for="name">Name:</label>
            <input type="text" id="name" name="name" required>
            <label for="age">Age:</label>
            <input type="number" id="age" name="age" required>
            <label for="contact">Contact:</label>
            <input type="text" id="contact" name="contact" required>
            <label for="medical_history">Medical History:</label>
            <textarea id="medical_history" name="medical_history" rows="3" required></textarea>
            <label for="current_condition">Current Condition:</label>
            <textarea id="current_condition" name="current_condition" rows="3" required></textarea>
            <button type="submit">Add Patient</button>
        </form>

        <h2>All Patients</h2>
        <table>
            <thead>
                <tr>
                    <th>Patient Number</th>
                    <th>Name</th>
                    <th>Age</th>
                    <th>Contact</th>
                    <th>Medical History</th>
                    <th>Current Condition</th>
                    <th>Actions</th>
                </tr>
            </thead>
            <tbody>
                <?php if ($patients) : ?>
                    <?php foreach ($patients as $patient) : ?>
                        <tr>
                            <td><?php echo $patient['count_number']; ?></td>
                            <td><?php echo $patient['name']; ?></td>
                            <td><?php echo $patient['age']; ?></td>
                            <td><?php echo $patient['contact']; ?></td>
                            <td><?php echo $patient['medical_history']; ?></td>
                            <td><?php echo $patient['current_condition']; ?></td>
                            <td>
                                <a href="edit.php?id=<?php echo $patient['id']; ?>" class="edit-btn">Edit</a>
                                <a href="delete.php?id=<?php echo $patient['id']; ?>" class="delete-btn" onclick="return confirm('Are you sure you want to delete this record?')">Delete</a>
                            </td>
                        </tr>
                    <?php endforeach; ?>
                <?php else : ?>
                    <tr><td colspan="7">No records found.</td></tr>
                <?php endif; ?>
            </tbody>
        </table>
    </div>
    <script src="main.js"></script>
</body>
</html>