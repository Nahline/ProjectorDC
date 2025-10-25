from flask import Flask, render_template, redirect, url_for # type: ignore
import requests
app = Flask(__name__)

ESP_IP = "http://127.0.0.1:8080"  # troque pelo IP da sua ESP


@app.route('/')
def index():
    estado = "Desconectado"
    try:
        r = requests.get(f"{ESP_IP}/relay/status", timeout=2)
        data = r.json()
        estado = "Ligado" if data.get("relay") == "on" else "Desligado"
    except:
        pass
    
    return render_template('index.html', estado=estado)

@app.route('/ligar')
def ligar():
    try:
        requests.get(f"{ESP_IP}/relay/on", timeout=2)
    except:
        pass
    return redirect(url_for('index'))

@app.route('/desligar')
def desligar():
    try:
        requests.get(f"{ESP_IP}/relay/off", timeout=2)
    except:
        pass
    return redirect(url_for('index'))


if __name__ == '__main__':
    app.run(debug=True)
