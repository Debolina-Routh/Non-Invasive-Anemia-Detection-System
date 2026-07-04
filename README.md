# 🩸 HemoSense
### AI-Powered Non-Invasive Anemia Detection System

![Status](https://img.shields.io/badge/Status-Completed-success)
![Platform](https://img.shields.io/badge/Platform-ESP8266-blue)
![Sensor](https://img.shields.io/badge/Sensor-MAX30102-red)
![ML](https://img.shields.io/badge/Machine%20Learning-Random%20Forest-orange)
![Accuracy](https://img.shields.io/badge/Accuracy-91%25-brightgreen)

---

## 📖 Overview

**HemoSense** is an AI-powered, hardware-based biomedical device designed for the **non-invasive detection of anemia**. The system utilizes the **MAX30102 optical sensor** to acquire photoplethysmography (PPG) signals from a fingertip. These physiological signals are processed using a **Random Forest Machine Learning model** to predict the likelihood of anemia without requiring blood samples.

The project aims to provide a rapid, painless, affordable, and portable screening solution, particularly beneficial in resource-limited settings and for preliminary health assessments.

---

## 🚨 Problem Statement

Conventional anemia diagnosis requires blood sample collection, laboratory equipment, and trained personnel. These methods can be invasive, time-consuming, and costly, limiting accessibility in rural and low-resource environments.

---

## 💡 Proposed Solution

HemoSense offers a portable, AI-powered screening system that:

- Uses optical sensing instead of blood collection
- Performs real-time physiological signal acquisition
- Applies Machine Learning for anemia prediction
- Displays results through the Blynk IoT platform
- Provides a low-cost and user-friendly screening solution

---

# ✨ Features

- 🩸 Non-invasive anemia screening
- 🤖 AI-powered prediction using Random Forest
- 📡 Real-time PPG signal acquisition
- 📲 IoT monitoring through Blynk
- 🔋 Portable and low-power design
- 💰 Cost-effective healthcare solution

---

# 🏗️ System Architecture

```
             Finger
                │
                ▼
          MAX30102 Sensor
                │
                ▼
             ESP8266
                │
                ▼
        Signal Processing
                │
                ▼
      Random Forest Model
                │
                ▼
      Anemia Prediction
                │
                ▼
          Blynk IoT Dashboard
```

---

# ⚙️ Hardware Components

| Component | Description |
|-----------|-------------|
| ESP8266 | Wi-Fi enabled microcontroller |
| MAX30102 | Optical PPG Sensor |
| Jumper Wires | Hardware connections |
| Breadboard | Circuit assembly |
| USB Power Supply | Device powering |

---

# 💻 Software & Tools

- Arduino IDE
- Python
- Google Colab / Jupyter Notebook
- ESP8266 Board Package
- Blynk IoT Platform
- Scikit-learn
- Pandas
- NumPy

---

# 🧠 Machine Learning Workflow

1. Data Collection
2. Data Preprocessing
3. Feature Extraction
4. Model Training
5. Random Forest Classification
6. Performance Evaluation
7. Real-Time Prediction

---

# 📊 Performance

| Metric | Value |
|--------|------|
| Machine Learning Model | Random Forest |
| Accuracy | **91%** |

---


# 📂 Repository Structure

```
HemoSense
│
├── Arduino_Code
├── Python_Code
├── Images
├── Circuit_Diagram
├── Documentation
├── Dataset
├── Results
└── README.md
```

---

# 🎯 Applications

- Early anemia screening
- Rural healthcare
- Primary health centers
- Remote patient monitoring
- Community health camps
- Preventive healthcare

---

# 🚀 Future Improvements

- Improve robustness against motion artifacts during signal acquisition.
- Train the model with larger and more diverse clinical datasets.
- Enhance prediction accuracy through advanced AI models such as XGBoost or deep learning.
- Develop a dedicated Android and iOS mobile application.
- Integrate cloud-based patient data storage and analytics.
- Design a compact PCB for a wearable version of the device.
- Conduct clinical validation with hospitals and healthcare institutions.
- Expand the system to estimate hemoglobin concentration continuously rather than only classifying anemia risk.

---

# 👨‍💻 Team

**Project Name:** HemoSense

**Team:** BioFusion

**Team Leader**
- Debolina Routh

---
# ⭐ Support

If you found this project interesting, please consider giving this repository a ⭐.
