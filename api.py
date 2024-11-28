from flask import Flask, jsonify, request
from flask_cors import CORS
import pymysql
from datetime import timedelta

app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})

# Conexión a la base de datos
def connect_db():
    return pymysql.connect(
        host="localhost", 
        user="webuser", 
        password="", 
        database="neurobox"
    )

# Ruta para obtener todos los datos combinados
@app.route('/all_data', methods=['GET'])
def get_all_data():
    try:
        # Conexión a la base de datos
        conn = connect_db()
        cursor = conn.cursor(pymysql.cursors.DictCursor)

        # Consulta con múltiples JOINs para combinar las tablas
        query = ""
        query = """
        
        SELECT 
            p.`ID_Paciente`,
            p.`Nombre` AS Nombre_Paciente,
            p.`Edad` AS Edad_Paciente,
            t.`Nombre` AS Nombre_Tutor,
            t.`Edad` AS Edad_Tutor,
            t.`Correo_Electronico` AS Correo_Tutor,
            e.`ID_Especialista`,
            e.`Nombre` AS Nombre_Especialista,
            e.`Correo Electrónico` AS Correo_Especialista,
            j.`ID_Juego`,
            j.`Nombre` AS Nombre_Juego,
            j.`Propósito` AS Proposito_Juego,
            j.`Duracion` AS Duracion_Juego,
            j.`Fecha` AS Fecha_Juego,
            r.`ID_Resultado`,
            r.`Puntuación` AS Puntuacion_Resultado,
            r.`Tipo` AS Tipo_Resultado
        FROM `paciente` p
        LEFT JOIN `tutor` t ON p.`ID_Paciente` = t.`ID_Paciente`
        LEFT JOIN `paciente_a_especialista` pae ON p.`ID_Paciente` = pae.`ID_Paciente`
        LEFT JOIN `especialista` e ON pae.`ID_Especialista` = e.`ID_Especialista`
        LEFT JOIN `paciente_a_resultado` par ON p.`ID_Paciente` = par.`ID_Paciente`
        LEFT JOIN `resultados` r ON par.`ID_Resultado` = r.`ID_Resultado`
        LEFT JOIN `juego` j ON r.`ID_Juego` = j.`ID_Juego`;
        """

        cursor.execute(query)
        results = cursor.fetchall()

        # Procesar resultados para convertir `timedelta` y valores nulos
        for row in results:
            if isinstance(row.get('Duracion_Juego'), timedelta):
                row['Duracion_Juego'] = str(row['Duracion_Juego'])  # Convertir timedelta a string
            row['Nombre_Tutor'] = row.get('Nombre_Tutor', 'N/A')
            row['Edad_Tutor'] = row.get('Edad_Tutor', 'N/A')
            row['Correo_Tutor'] = row.get('Correo_Tutor', 'N/A')
            row['Nombre_Especialista'] = row.get('Nombre_Especialista', 'N/A')
            row['Correo_Especialista'] = row.get('Correo_Especialista', 'N/A')
            row['Proposito_Juego'] = row.get('Proposito_Juego', 'N/A')
            row['Duracion_Juego'] = row.get('Duracion_Juego', 'N/A')
            row['Fecha_Juego'] = row.get('Fecha_Juego', 'N/A')
            row['Puntuacion_Resultado'] = row.get('Puntuacion_Resultado', 'N/A')
            row['Tipo_Resultado'] = row.get('Tipo_Resultado', 'N/A')

        return jsonify(results)

    except pymysql.MySQLError as e:
        print(f"Database error: {e}")
        return jsonify({"error": "Database query failed"}), 500

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({"error": "Internal server error"}), 500

    finally:
        conn.close()


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
