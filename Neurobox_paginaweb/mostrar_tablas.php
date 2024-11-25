<?php
// Configuración de la base de datos
$host = 'localhost'; // O la dirección de tu servidor de base de datos
$usuario = 'root'; // Reemplaza con tu usuario de MariaDB
$contrasena = ''; // Reemplaza con la contraseña de tu base de datos
$base_datos = 'neurobox'; // Tu base de datos

// Conectar a la base de datos
$conexion = new mysqli($host, $usuario, $contrasena, $base_datos);

// Verificar la conexión
if ($conexion->connect_error) {
    die("Conexión fallida: " . $conexion->connect_error);
}

// Consulta SQL para obtener los datos de la tabla (ajusta el nombre de la tabla)
$consulta = "SELECT * FROM nombre_de_tu_tabla"; // Reemplaza con el nombre real de la tabla
$resultado = $conexion->query($consulta);

// Mostrar los datos en una tabla HTML
if ($resultado->num_rows > 0) {
    echo "<table border='1'><tr>";

    // Crear los encabezados de columna
    while ($campo = $resultado->fetch_field()) {
        echo "<th>" . $campo->name . "</th>";
    }
    echo "</tr>";

    // Llenar la tabla con los datos
    while ($fila = $resultado->fetch_assoc()) {
        echo "<tr>";
        foreach ($fila as $dato) {
            echo "<td>" . $dato . "</td>";
        }
        echo "</tr>";
    }
    echo "</table>";
} else {
    echo "No hay datos disponibles";
}

// Cerrar la conexión
$conexion->close();
?>
