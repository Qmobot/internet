// Данный кусочек кода отвечает за внедрения "Шапки", в которой прописаны детали библиотеки
#include "qmobot.h"
#include <WiFi.h> // Библиотека по работе с Вай-Фай и интернетом

// Данные глобальные переменные нужны для функции ленты
int line = 0;
String phrases[5] = {"", "", "", "", ""};

// Данные переменные хранят имя сети и пароль
// const char* - особая форма хранения букв, звездочка в конце обозначает строку, а const, что строка не будет меняться.
const char* ssid = "SSID or name of WiFI";
const char* password = "Password";

// Мы создаем обьект сервера на порте 80, то есть мы слушаем, что к нам придет на 80-м порте из сети.
WiFiServer wifiServer(80);

// Декларация функций.
void displayPhrase(String Phrase);
void displayLenta(String Phrase);
void analyze(String command);

// Настройка чипа
void setup(){
  delay(2000);
    Qchip.begin(
      /* Нужно ли подключать экран - Да */true, 
      /* Нужно ли подключение по последовательному порту? - Да */true
        );
  
  // Данная функция, говорит чипу, что у него есть встроенная LED лампочка и
  // необходимо перевести ее в режим вывода данных, чтобы включать и выключать
  pinMode(LED_BUILTIN, OUTPUT);

  // Подключаемся к ВайФай
  WiFi.begin(ssid, password);
 
  // Пока не подключимся, писать, что мы подключаемся.
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  // При подключении, написать наш IP адрес.
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());

  // Написать наш IP адрес на экране.
  displayPhrase("");
 
  // Начать слушать 80-й порт.
  wifiServer.begin();

}

// Данная часть кода будет выпонятся постоянно в цикле
void loop() {
 
  // Создавать переменную для каждого клиента сервера
  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
      
      String Phrase = "";

      while (client.available()>0) {
        char c = client.read();
        client.write(c);
        if(c!='\n' && isPrintable(c)){
          Phrase += c;
        }
      }
      if(Phrase != ""){
        displayPhrase(Phrase);
        // displayLenta(Phrase);
        Serial.print("Phrase is: ");
        Serial.println(Phrase);
        delay(10);
      }
      if(Phrase == "Bye"){
        client.stop();
        displayPhrase("Bye-bye!");
        Serial.print("Bye-Bye!");
        Serial.println(Phrase);
        delay(10);
      }
      analyze(Phrase);
    }

    client.stop();
    Serial.println("Client disconnected");
 
  }
}


void displayPhrase(String Phrase){
  Qchip.display->clear(); // Очистить дисплей от надписей
                          // Пиксели по x,      пиксели по y,     текст
  Qchip.display->drawString( 0 /*от 0 до 128*/, 0 /*от 0 до 64*/, (WiFi.localIP().toString()+":80")); // Написать текст на дисплее
  Qchip.display->drawString( 0 /*от 0 до 128*/, 30 /*от 0 до 64*/, Phrase); // Написать текст на дисплее
  Qchip.display->display(); // Показать на дисплее
}

void displayLenta(String Phrase){
  if(line<4){
    Qchip.display->drawString( 0 , (line*10 + 10), Phrase);
    line++;
    phrases[line] = Phrase;
  }
  else{
    Qchip.display->clear(); 
    for(int i = 0; i<=4; i++){
      if(i==4){
        phrases[i] = Phrase;
      }
      else{
        phrases[i] = phrases[i+1];
      }
      Qchip.display->drawString(0, (i*10 + 10), phrases[i]);
    }
  }
  Qchip.display->drawString( 0, 0, (WiFi.localIP().toString()+":80"));
  Qchip.display->display();
}

void analyze(String command){
  if(command == "On"){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if(command == "Off"){
    digitalWrite(LED_BUILTIN, LOW);
  }
}