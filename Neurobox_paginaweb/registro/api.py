from flask import Flask, request, jsonify
from flask_cors import CORS
import pymysql

app = Flask(__name__)
CORS(app)

# Configura la conexión a la base de datos
db_config = {
    'host': 'localhost',           # Cambia a la IP de tu Raspberry cuando sea necesario
    'user': 'tu_usuario',          # Cambia por tu usuario de MariaDB
    'password': 'tu_contraseña',   # Cambia por tu contraseña de MariaDB
    'database': 'neurobox'
}

# Función para manejar la conexión a la base de datos
def get_db_connection():
    return pymysql.connect(
        host=db_config['host'],
        user=db_config['user'],
        password=db_config['password'],
        database=db_config['database'],
        cursorclass=pymysql.cursors.DictCursor  # Devuelve resultados como diccionarios
    )

# Ruta de inicio de sesión
@app.route('/login', methods=['POST'])
def login():
    try:
        data = request.get_json()
        nombre = data.get('name')
        contraseña = data.get('password')

        if not nombre or not contraseña:
            return jsonify({"status": "error", "message": "Nombre de usuario y contraseña son requeridos"}), 400

        connection = get_db_connection()
        with connection.cursor() as cursor:
            sql = "SELECT * FROM usuarios WHERE nombre=%s AND contraseña=%s"
            cursor.execute(sql, (nombre, contraseña))
            usuario = cursor.fetchone()

        connection.close()

        if usuario:
            return jsonify({"status": "success", "redirect": "HTML_neurobox.html"})
        else:
            return jsonify({"status": "error", "message": "Usuario o contraseña incorrectos"})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

# Ruta para registrar un nuevo usuario
@app.route('/registro', methods=['POST'])
def registro():
    try:
        data = request.get_json()
        nombre = data.get('name')
        contraseña = data.get('password')

        if not nombre or not contraseña:
            return jsonify({"status": "error", "message": "Nombre de usuario y contraseña son requeridos"}), 400

        connection = get_db_connection()
        with connection.cursor() as cursor:
            sql = "INSERT INTO usuarios (nombre, contraseña) VALUES (%s, %s)"
            cursor.execute(sql, (nombre, contraseña))
            connection.commit()

        connection.close()
        return jsonify({"status": "success", "message": "Usuario registrado exitosamente"})
    except pymysql.err.IntegrityError:
        return jsonify({"status": "error", "message": "El usuario ya existe"}), 400
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
