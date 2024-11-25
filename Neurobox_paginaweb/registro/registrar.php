<?php
include("conexion.php");

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = trim($_POST["name"]);
    $password = password_hash(trim($_POST["password"]), PASSWORD_DEFAULT);

    $consulta = "INSERT INTO usuarios (nombre, contraseña) VALUES (?, ?)";
    $stmt = mysqli_prepare($conex, $consulta);
    mysqli_stmt_bind_param($stmt, "ss", $name, $password);

    if (mysqli_stmt_execute($stmt)) {
        echo "<script>alert('Usuario registrado exitosamente'); window.location.href='index.php';</script>";
    } else {
        echo "<p style='color: red;'>Error al registrar usuario.</p>";
    }
}
?>
