<?php
    $conex = mysqli_connect("localhost", "root", "", "registro");

    if (!$conex) {
        die("Conexión fallida: " . mysqli_connect_error());
    }

    if (isset($_POST["register"])) {

        if (strlen($_POST["name"]) >= 1 && strlen($_POST["password"]) >= 1) {

            $name = trim($_POST["name"]);
            $password = trim($_POST["password"]);
            // Encriptar la contraseña
            $hashed_password = password_hash($password, PASSWORD_DEFAULT);
            
            // Corregir la consulta SQL
            $consulta = "INSERT INTO datos(nombre, contraseña) VALUES('$name', '$hashed_password')";
            $resultado = mysqli_query($conex, $consulta);
            
            if ($resultado) {
                echo '<h3 class="success">Tu registro se ha completado</h3>';
            } else {
                echo '<h3 class="error">Ocurrió un error</h3>';
            }
        }
    }
?>
