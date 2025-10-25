#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ===== CONFIGURAÇÕES DE REDE =====
const char* ssid = "SEU_SSID";       // Nome da rede Wi-Fi
const char* password = "SUA_SENHA";  // Senha da rede Wi-Fi

// ===== CONFIGURAÇÕES DO RELÉ =====
#define RELAY_PIN 5 // GPIO5 (D1 na NodeMCU)
const bool RELAY_ACTIVE_LOW = true;  // true = LOW liga o relé, false = HIGH liga

// ===== SERVIDOR WEB =====
ESP8266WebServer server(80);

// 🔹 Cria um atalho para registrar endpoints GET
#define get(path, handler) server.on(path, HTTP_GET, handler)

// Estado atual do relé
bool relayState = false;

// ===== FUNÇÃO PARA CONTROLAR O RELÉ =====
void setRelay(bool on) {
  relayState = on;
  if (RELAY_ACTIVE_LOW) digitalWrite(RELAY_PIN, on ? LOW : HIGH);
  else digitalWrite(RELAY_PIN, on ? HIGH : LOW);
}

// ===== FUNÇÃO PARA RETORNAR STATUS EM JSON =====
String jsonStatus() {
  String s = "{ \"ok\": true, \"relay\": \"";
  s += relayState ? "on" : "off";
  s += "\" }";
  return s;
}

// ===== ENDPOINT PRINCIPAL "/" =====
void handleRoot() {
  String html = "<html><body><h1>ESP8266 Relay Controller</h1>";
  html += "<p>Status: ";
  html += relayState ? "ON" : "OFF";
  html += "</p>";
  html += "<a href=\"/relay/on\">ligar</a><br>";
  html += "<a href=\"/relay/off\">desligar</a><br>";
  html += "<a href=\"/relay/status\">status JSON</a><br>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// ===== ENDPOINT /relay/status =====
void handleStatus() {
  server.send(200, "application/json", jsonStatus());
}

// ===== ENDPOINT /relay/on =====
void handleOn() {
  setRelay(true);
  server.send(200, "application/json", jsonStatus());
}

// ===== ENDPOINT /relay/off =====
void handleOff() {
  setRelay(false);
  server.send(200, "application/json", jsonStatus());
}

// ===== CASO ACESSE UMA ROTA INEXISTENTE =====
void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}

// ===== SETUP INICIAL =====
void setup() {
  Serial.begin(115200);

  // Configura o pino do relé
  pinMode(RELAY_PIN, OUTPUT);
  if (RELAY_ACTIVE_LOW) digitalWrite(RELAY_PIN, HIGH);
  else digitalWrite(RELAY_PIN, LOW);

  // Conecta ao Wi-Fi
  Serial.print("Conectando-se ao Wi-Fi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // ===== REGISTRO DOS ENDPOINTS (GET) =====
  get("/", handleRoot);
  get("/relay/status", handleStatus);
  get("/relay/on", handleOn);
  get("/relay/off", handleOff);
  server.onNotFound(handleNotFound);

  // Inicia o servidor HTTP
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

// ===== LOOP PRINCIPAL =====
void loop() {
  server.handleClient(); // processa requisições HTTP
}
