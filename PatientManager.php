<?php
class PatientManager {
    private $conn;

    public function __construct($conn) {
        $this->conn = $conn;
    }

    public function getPatients() {
        $query = "SELECT * FROM patients ORDER BY count_number";
        $result = mysqli_query($this->conn, $query);

        if ($result && mysqli_num_rows($result) > 0) {
            return mysqli_fetch_all($result, MYSQLI_ASSOC);
        }
        return null;
    }

    public function addPatient($name, $age, $contact, $medicalHistory, $currentCondition) {
        $query = "SELECT MAX(count_number) AS max_count FROM patients";
        $result = mysqli_query($this->conn, $query);
        $row = mysqli_fetch_assoc($result);
        $count_number = $row['max_count'] + 1;

        $query = "INSERT INTO patients (name, age, contact, medical_history, current_condition, count_number)
                  VALUES ('$name', '$age', '$contact', '$medicalHistory', '$currentCondition', $count_number)";
        return mysqli_query($this->conn, $query);
    }

    public function updatePatient($id, $name, $age, $contact, $medicalHistory, $currentCondition) {
        $query = "UPDATE patients 
                  SET name = '$name', age = '$age', contact = '$contact', 
                      medical_history = '$medicalHistory', current_condition = '$currentCondition'
                  WHERE id = $id";
        return mysqli_query($this->conn, $query);
    }

    public function deletePatient($id) {
        $query = "DELETE FROM patients WHERE id = $id";
        return mysqli_query($this->conn, $query);
    }

    public function updatePatientNumbers() {
        $query = "SET @count = 0;";
        mysqli_query($this->conn, $query);

        $query = "UPDATE patients SET count_number = (@count := @count + 1) ORDER BY count_number";
        mysqli_query($this->conn, $query);
    }
}
?>
