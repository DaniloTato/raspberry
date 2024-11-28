from flask import Flask, jsonify, request
from flask_cors import CORS
import pymysql

app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})


def connect_db():
    return pymysql.connect(
        host="localhost",
        user="webuser",
        password="",
        database="neurobox_v3"  # Cambiado a neurobox_v3
    )


@app.route('/data', methods=['GET'])
def get_data():
    conn = None  # Inicializa la conexión como None
    try:
        id_juego = request.args.get('id_juego')
        tipo = request.args.get('tipo')

        conn = connect_db()  # Intenta conectarte a la base de datos
        cursor = conn.cursor()

        query = "SELECT * FROM resultados WHERE 1=1"
        params = []

        if id_juego:
            query += " AND id_juego = %s"
            params.append(id_juego)
        
        if tipo:
            query += " AND tipo = %s"
            params.append(tipo)

        cursor.execute(query, params)
        rows = cursor.fetchall()

        if not rows:
            return jsonify({"error": "No data found"}), 404

        columns = [col[0] for col in cursor.description]
        data = [dict(zip(columns, row)) for row in rows]
        return jsonify(data)

    except pymysql.MySQLError as e:
        return jsonify({"error": f"Database error: {e}"}), 500

    except Exception as e:
        return jsonify({"error": f"Error: {e}"}), 500

    finally:
        if conn:  # Solo cierra la conexión si fue creada
            conn.close()


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)