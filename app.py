# app.py

from flask import Flask
from controllers.auth_controller import auth_bp

app = Flask(__name__)
app.register_blueprint(auth_bp, url_prefix="/api")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
