<?php
$conn = mysqli_connect("localhost", "root", "", "patients_db");

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
?>