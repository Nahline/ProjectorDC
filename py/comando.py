from flask import Flask, render_template, redirect, url_for # type: ignore

app = Flask(__name__)

# Estado do ar-condicionado (False = desligado, True = ligado)
ar_condicionado_ligado = False

@app.route('/')
def index():
    estado = "Ligado" if ar_condicionado_ligado else "Desligado"
    return render_template('index.html', estado=estado)

@app.route('/ligar')
def ligar():
    global ar_condicionado_ligado
    ar_condicionado_ligado = True
    return redirect(url_for('index'))

@app.route('/desligar')
def desligar():
    global ar_condicionado_ligado
    ar_condicionado_ligado = False
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)
