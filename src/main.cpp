#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <stdio.h>

#define BETA 3950
#define SS 10

int analogValue;
float celcius ;
const char *file = "fileName.txt";
File arquivo;


void main_loop();
void open_file();
void read_file();

void setup() {
  //start librarys
  SPI.begin();
  Serial.begin(115200);

  //initializing the SD card memory
  if (!SD.begin(SS)){
    Serial.println("SD card do not opened!");
  }
  Serial.println("SD card opened!");
  
  //setting the pins
  pinMode(SS, OUTPUT);
  pinMode(A0, INPUT);
  
  int i = analogRead(A0);
  main_loop();

  //Write value 
  while (true){
    if (i != analogRead(A0)){
      main_loop();
    }
    i = analogRead(A0);
  }
 
}

void loop() {}

void main_loop(){

  //Transforming de analog value in an digital value "°c"
  analogValue = analogRead(A0);
  celcius = 1 / (log(1 / (1023.0 / analogValue - 1)) / BETA + 1/298.15) - 273.15;


  //open/creating a file on SD card 
  //for write de value taked in temperature-sensor
  open_file();
  
  //open and write information in Serial terminal
  read_file();
  //
}


void open_file(){
  arquivo = SD.open(file, FILE_WRITE);
  if (arquivo){
    arquivo.print(celcius);
    arquivo.println("°C");
    Serial.println("info write sucessful.");
    arquivo.close();  
    
  }else{
    Serial.println("Error: info did'n write.");
  }
}

void read_file(){
  arquivo = SD.open(file, FILE_READ);
  if(arquivo){
    Serial.println("informação:");
    while (arquivo.available()){
      Serial.write(arquivo.read());
    }
    arquivo.close();
  }else{
    Serial.println("Arquivo não aberto.");
  }

}