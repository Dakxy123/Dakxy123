<?php
require_once 'db_connect.php';
require_once 'PatientManager.php';

$patientManager = new PatientManager($conn);

if (isset($_GET['id'])) {
    $id = $_GET['id'];
    $patientManager->deletePatient($id);
    $patientManager->updatePatientNumbers();
    header("Location: index.php");
}
?>