<?php
include("conexion.php"); // (Mensaje para danilo, asegúrate de que la conexión es correcta.

session_start();

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = trim($_POST["name"]);
    $password = trim($_POST["password"]);

    $consulta = "SELECT * FROM usuarios WHERE nombre = ?";
    $stmt = mysqli_prepare($conex, $consulta);
    mysqli_stmt_bind_param($stmt, "s", $name);
    mysqli_stmt_execute($stmt);
    $resultado = mysqli_stmt_get_result($stmt);

    if ($row = mysqli_fetch_assoc($resultado)) {
        if (password_verify($password, $row['contraseña'])) {
            // Inicia sesión y redirige al usuario
            $_SESSION["usuario"] = $name;
            header("Location: Html_neurobox.html");
            exit();
        } else {
            echo "<p style='color: red;'>Contraseña incorrecta.</p>";
        }
    } else {
        echo "<p style='color: red;'>Usuario no encontrado.</p>";
    }
}
?>
