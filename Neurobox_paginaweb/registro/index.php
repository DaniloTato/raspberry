<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Inicio de Sesión</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

    <div class="formulario">
        <h1>Inicio de Sesión</h1>
<form method="post" action="login.php">
    <div class="username">
        <input type="text" id="username" name="name" required>
        <label for="username">Nombre de Usuario</label>
    </div>
    <div class="password">
        <input type="password" id="password" name="password" required>
        <label for="password">Contraseña</label>
    </div>
    <input type="submit" value="Iniciar" class="btn">
</form>

    </div>

    <?php
        include("registrar.php");
    ?>
</body>
</html>
