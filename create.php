<?php
require_once 'db_connect.php';
require_once 'PatientManager.php';

$patientManager = new PatientManager($conn);

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $name = $_POST['name'];
    $age = $_POST['age'];
    $contact = $_POST['contact'];
    $medicalHistory = $_POST['medical_history'];
    $currentCondition = $_POST['current_condition'];

    $patientManager->addPatient($name, $age, $contact, $medicalHistory, $currentCondition);
    header("Location: index.php");
}
?>