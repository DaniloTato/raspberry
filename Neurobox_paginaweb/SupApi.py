from flask import Flask, jsonify, request
from flask_cors import CORS
import pymysql
from datetime import timedelta
import logging

logging.basicConfig(level=logging.DEBUG)

app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})

# Conexión a la base de datos
def connect_db():
    return pymysql.connect(
        host="localhost",
        user="webuser",
        password="",  # Asegúrate de que este campo sea correcto
        database="neurobox"
    )

# Ruta para obtener todos los datos combinados con soporte de filtros
@app.route('/all_data', methods=['GET'])
def get_all_data():
    conn = None
    try:
        logging.debug('Conectando a la base de datos...')
        conn = connect_db()
        cursor = conn.cursor(pymysql.cursors.DictCursor)

        # Obtener parámetros de filtro desde la URL
        id_juego = request.args.get('id_juego')
        id_paciente = request.args.get('id_paciente')
        id_especialista = request.args.get('id_especialista')
        id_resultado = request.args.get('id_resultado')

        # Construcción de la consulta con filtros opcionales
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
        LEFT JOIN `juego` j ON r.`ID_Juego` = j.`ID_Juego`
        WHERE (%s IS NULL OR j.`ID_Juego` = %s)
          AND (%s IS NULL OR p.`ID_Paciente` = %s)
          AND (%s IS NULL OR e.`ID_Especialista` = %s)
          AND (%s IS NULL OR r.`ID_Resultado` = %s);
        """
        logging.debug('Ejecutando consulta SQL...')
        cursor.execute(query, (id_juego, id_juego, id_paciente, id_paciente, id_especialista, id_especialista, id_resultado, id_resultado))
        results = cursor.fetchall()
        logging.debug('Consulta ejecutada exitosamente.')

        # Procesar resultados para convertir `timedelta` y valores nulos
        for row in results:
            if isinstance(row.get('Duracion_Juego'), timedelta):
                row['Duracion_Juego'] = str(row['Duracion_Juego'])  # Convertir timedelta a string
            row['Nombre_Tutor'] = row.get('Nombre_Tutor') or 'N/A'
            row['Edad_Tutor'] = row.get('Edad_Tutor') or 'N/A'
            row['Correo_Tutor'] = row.get('Correo_Tutor') or 'N/A'
            row['Nombre_Especialista'] = row.get('Nombre_Especialista') or 'N/A'
            row['Correo_Especialista'] = row.get('Correo_Especialista') or 'N/A'
            row['Proposito_Juego'] = row.get('Proposito_Juego') or 'N/A'
            row['Duracion_Juego'] = row.get('Duracion_Juego') or 'N/A'
            row['Fecha_Juego'] = row.get('Fecha_Juego') or 'N/A'
            row['Puntuacion_Resultado'] = row.get('Puntuacion_Resultado') or 'N/A'
            row['Tipo_Resultado'] = row.get('Tipo_Resultado') or 'N/A'

        return jsonify(results)

    except pymysql.MySQLError as e:
        logging.error(f"Database error: {e}")
        return jsonify({"error": "Database query failed"}), 500

    except Exception as e:
        import traceback
        traceback.print_exc()
        logging.error(f"Error: {e}")
        return jsonify({"error": "Internal server error"}), 500

    finally:
        if conn:
            conn.close()

# Ruta para obtener las puntuaciones para un paciente y un juego específico
@app.route('/filtered_data', methods=['GET'])
def get_filtered_data():
    conn = None
    try:
        id_paciente = request.args.get('id_paciente', None)
        id_juego = request.args.get('id_juego', None)

        # Valida si los parámetros son correctos
        if not id_paciente or not id_juego:
            return jsonify({"error": "Faltan parámetros 'id_paciente' o 'id_juego'"}), 400

        conn = connect_db()
        cursor = conn.cursor(pymysql.cursors.DictCursor)

        query = """
            SELECT r.`Puntuación` AS puntuacion, j.`Fecha` AS fecha
            FROM `paciente` p
            JOIN `paciente_a_resultado` par ON p.`ID_Paciente` = par.`ID_Paciente`
            JOIN `resultados` r ON par.`ID_Resultado` = r.`ID_Resultado`
            JOIN `juego` j ON r.`ID_Juego` = j.`ID_Juego`
            WHERE p.`ID_Paciente` = %s AND j.`ID_Juego` = %s
            ORDER BY j.`Fecha` ASC;
        """
        cursor.execute(query, (id_paciente, id_juego))
        results = cursor.fetchall()

        if not results:
            return jsonify({"error": "No hay datos disponibles para estos filtros"}), 404

        # Convertir fechas a string para JSON
        for row in results:
            row['fecha'] = row['fecha'].strftime('%Y-%m-%d') if row['fecha'] else 'Sin fecha'

        return jsonify(results)

    except pymysql.MySQLError as e:
        logging.error(f"Database error: {e}")
        return jsonify({"error": "Database query failed"}), 500

    except Exception as e:
        import traceback
        traceback.print_exc()
        logging.error(f"Error: {e}")
        return jsonify({"error": "Internal server error"}), 500

    finally:
        if conn:
            conn.close()

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
