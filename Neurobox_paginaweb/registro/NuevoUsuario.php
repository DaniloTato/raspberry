<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="utf-8">
    <title>Nuevo Usuario</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Registrar Nuevo Usuario</h1>
    <form method="post" action="registrar_usuario.php">
        <div class="username">
            <input type="text" name="name" required>
            <label>Nombre de Usuario</label>
        </div>
        <div class="password">
            <input type="password" name="password" required>
            <label>Contraseña</label>
        </div>
        <input type="submit" value="Registrar" class="btn">
    </form>
</body>
</html>
