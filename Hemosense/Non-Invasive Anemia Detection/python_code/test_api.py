import requests

url = "http://192.168.29.166:5000//predict"   # ← your Flask IP

data = {
    "red": 1200,
    "ir": 2200,
    "age": 22,
    "gender": 0
}

print("Sending request...")
response = requests.post(url, json=data)
print("Status code:", response.status_code)
print("Response:", response.json())