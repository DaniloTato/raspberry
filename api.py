from flask import Flask, jsonify, request
from flask_cors import CORS
import pymysql

app = Flask(__name__)
CORS(app)  # Permitir solicitudes desde cualquier origen

def connect_db():
    return pymysql.connect(
        host="localhost", 
        user="webuser", 
        password="", 
        database="neurobox"
    )

@app.route('/data', methods=['GET'])
def get_data():
    try:
        #get filtros
        id_juego = request.args.get('id_juego')
        tipo = request.args.get('tipo')

        #conexion
        conn = connect_db()
        cursor = conn.cursor()

        # query con los filtros
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
        print(f"Database error: {e}")
        return jsonify({"error": "Database query failed"}), 500

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({"error": "Internal server error"}), 500

    finally:
        conn.close()

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)