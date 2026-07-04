from flask import Flask, request, jsonify
import joblib
import numpy as np
import pandas as pd

app = Flask(__name__)

model = joblib.load("hemoglobin_model.pkl")

@app.route('/')
def home():
    return "Flask server is running ✅"

@app.route('/predict', methods=['POST'])
def predict():
    data = request.json

    red = data['red']
    ir = data['ir']
    age = data['age']
    gender = data['gender']

    ratio = red / ir

    features = pd.DataFrame([[red, ir, ratio, age, gender]], columns=['Red (a.u)', 'Infra Red (a.u)', 'ratio', 'Age (year)', 'Gender'])

    hb = model.predict(features)[0]

    return jsonify({"hb": hb})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)