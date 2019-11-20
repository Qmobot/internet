// Данный кусочек кода отвечает за внедрения "Шапки", в которой прописаны детали библиотеки
#include "qmobot.h"
#include <WiFi.h>

// Есть два вида комментариев:
// 1. Комментарии, которые начинаются и идут на всю линию с "// Comment"
// 2. Комментарии на отрывок, которые идут внутри скобок "/* Comment */"

// Декларируем все функции, чтобы программа знала, что такие функции есть
void displayIt(String t); 
void chat(); 
int minusSum(int n, int player);
void primer();

// Настройка чипа
void setup(){
  delay(2000);
    Qchip.begin(
      /* Нужно ли подключать экран - Да */true, 
      /* Нужно ли подключение по последовательному порту? - Да */true
        );
  
  // primer();
  // chat();
  // displayIt("I love QMOBOT");

}

// Данная часть кода будет выпонятся постоянно в цикле
void loop(){
    
}

// Создаем функцию чата:
// Qchip умеет не только писать что-то в вывод последовательного порта,
// но может и считывать оттуда, то есть мы можем написать некий чат.

// Рекурсивная функция, которая возращает сумму обратной прогрессии до нуля
// minusSum(5) = 4 + 3 + 2 + 1 + 0 = 10

int minusSum(int n, int player){
  Serial.print("Я игрок №");
  Serial.println(player);
  Serial.print("Мне пришла цифра: ");
  Serial.println(n);
  if(n>0){
    Serial.println("Моя цифра больше нуля");
    Serial.print("Я отправляю игроку ниже цифру: ");
    Serial.println(n-1);
    Serial.println();
    n = n - 1 + minusSum(n-1, player + 1);
  }else{
    Serial.println("Моя цифра меньше нуля");
    Serial.println();
    n =  0;
  }
  Serial.print(player);
  Serial.print(" возвращает ");
  Serial.println(n);
  Serial.println();
  return n;
}

void primer(){
  Serial.println("====================================");
  Serial.println("Пример с 6-ю игроками:");
  int summ = minusSum(6, 0);
  Serial.println("====================================");
  Serial.println();
}

void chat(){
  Serial.println();
  Serial.println("Функция обратной прогрессии: ");
  Serial.println();

  while(true){
    Serial.print("Введите число: ");
    String value;
    while(Serial.available() == 0) {}
    while(Serial.available()){
      value = Serial.readString();
      Serial.print("Рекурсия до ");
      int ba = value.toInt();
      Serial.print(ba);
      Serial.print(": ");
      Serial.println("====================================");
      Serial.println(minusSum(ba, 0));
      Serial.println("====================================");
    }

    break; // Закрытие цикла не через условие осуществляется с помощью break
  }
}

void displayIt(String t){
  Qchip.display->clear(); // Очистить дисплей от надписей
                          // Пиксели по x,      пиксели по y,     текст
  Qchip.display->drawString( 0 /*от 0 до 128*/, 0 /*от 0 до 64*/, "Failure"); // Написать текст на дисплее
  Qchip.display->drawString(0, 0, "--------");
  Qchip.display->drawString(20,20, "Ospan");
  Qchip.display->display(); // Показать на дисплее
}


