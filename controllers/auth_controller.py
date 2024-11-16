# controllers/auth_controller.py

from flask import Blueprint, request, jsonify
from services.mqtt_service import control_led

auth_bp = Blueprint("auth", __name__)

@auth_bp.route("/login", methods=["POST"])
def login():
    data = request.json
    if data.get("username") == "user" and data.get("password") == "password":
        control_led(True)  # Kirim pesan "ON" setiap kali login
        return jsonify({"message": "Login successful"}), 200
    return jsonify({"message": "Invalid credentials"}), 401


@auth_bp.route("/logout", methods=["POST"])
def logout():
    control_led(False)  # Mematikan LED saat logout
    return jsonify({"message": "Logout successful"}), 200
