from flask import Flask, jsonify, request
from flask_cors import CORS
import pymysql
from datetime import timedelta

app = Flask(__name__)
CORS(app, resources={r"/": {"origins": ""}})

# Conexión a la base de datos
def connect_db():
    return pymysql.connect(
        host="localhost", 
        user="webuser", 
        password="", 
        database="neurobox"
    )

# Ruta para obtener los resultados filtrados por paciente y juego
@app.route('/scores', methods=['GET'])
def get_scores():
    try:
        paciente_id = request.args.get('paciente')
        juego_id = request.args.get('juego')

        # Conexión a la base de datos
        conn = connect_db()
        cursor = conn.cursor(pymysql.cursors.DictCursor)

        # Consulta con filtros de paciente y juego
        query = """
        SELECT 
            j.Fecha AS Fecha_Juego,
            r.Puntuación AS Puntuacion_Resultado
        FROM juego j
        JOIN resultados r ON j.ID_Juego = r.ID_Juego
        JOIN paciente_a_resultado par ON r.ID_Resultado = par.ID_Resultado
        WHERE par.ID_Paciente = %s AND j.ID_Juego = %s
        """

        cursor.execute(query, (paciente_id, juego_id))
        results = cursor.fetchall()

        # Procesar resultados
        for row in results:
            row['Fecha_Juego'] = str(row['Fecha_Juego'])  # Convertir a string

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