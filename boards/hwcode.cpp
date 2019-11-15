// Данный кусочек кода отвечает за внедрения "Шапки", в которой прописаны детали библиотеки
#include "qmobot.h"

int line = 0;
int vals[6] = {-1, -1, -1, -1, -1, -1};

// Есть два вида комментариев:
// 1. Комментарии, которые начинаются и идут на всю линию с "// Comment"
// 2. Комментарии на отрывок, которые идут внутри скобок "/* Comment */"

// Декларируем все функции, чтобы программа знала, что такие функции есть
int minusSum(int n, int player);

// Настройка чипа
void setup(){
  delay(2000);
    Qchip.begin(
      /* Нужно ли подключать экран - Да */true, 
      /* Нужно ли подключение по последовательному порту? - Да */true
        );
}

// Данная часть кода будет выпонятся постоянно в цикле
void loop(){
    Serial.print("Введите число: ");
    String value;
    while(Serial.available() == 0) {}
    while(Serial.available()){
      value = Serial.readString();
      Serial.print("Рекурсия до ");
      int ba = value.toInt();
      Serial.print(ba);
      Serial.print(": ");
      Serial.println("====================================");\
      int val = minusSum(ba, 0);

        if(line > 5){
          line = 6;
          for(int i = 1; i < 6; i++){
            vals[i-1] = vals[i];
          }
          vals[5] = val;
        }
        else{
          vals[line] = val;
          line ++;
        }
        Qchip.display->clear();
        String text;
        for(int i = 0; i < 6; i++){
          if(vals[i]>=0){
            text = String(vals[i]);
            Qchip.display->drawString(0, i*10, text);
          }
        }
        Qchip.display->display();


      Serial.println(val);
      Serial.println("====================================");
    }
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
