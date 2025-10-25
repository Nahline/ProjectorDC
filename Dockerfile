# Usa uma imagem oficial do Python como base
FROM python:3.11-slim

# Define o diretório de trabalho dentro do container
WORKDIR /app

# Copia os arquivos do projeto para dentro do container
COPY . .

# Instala as dependências do projeto
RUN pip install --no-cache-dir -r requirements.txt

# Expõe a porta usada pela aplicação Flask
EXPOSE 5000

# Define a variável de ambiente para o Flask
ENV FLASK_APP=comando.py
ENV FLASK_RUN_HOST=0.0.0.0

# Comando para iniciar o servidor
CMD ["flask", "run"]
