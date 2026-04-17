int ledDedoPulgar = 2;
int ledDedoIndice = 3;
int ledDedoMedio = 4;
int ledDedoAnular = 5;
int ledDedoMenique = 6;
char option;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledDedoPulgar, OUTPUT);
  pinMode(ledDedoIndice, OUTPUT);
  pinMode(ledDedoMedio, OUTPUT);
  pinMode(ledDedoAnular, OUTPUT);
  pinMode(ledDedoMenique, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    Serial.print("Datos recibidos: ");
    option = Serial.read();
    Serial.println(option);

    if(option == 'a'){
      digitalWrite(ledDedoPulgar, HIGH);
    }
    if(option == 'b'){
      digitalWrite(ledDedoPulgar, LOW);
    }

    if(option == 'c'){
      digitalWrite(ledDedoIndice, HIGH);
    }
    if(option == 'd'){
      digitalWrite(ledDedoIndice, LOW);
    }

    if(option == 'e'){
      digitalWrite(ledDedoMedio, HIGH);
    }
    if(option == 'f'){
      digitalWrite(ledDedoMedio, LOW);
    }

    if(option == 'g'){
      digitalWrite(ledDedoAnular, HIGH);
    }
    if(option == 'h'){
      digitalWrite(ledDedoAnular, LOW);
    }

    if(option == 'i'){
      digitalWrite(ledDedoMenique, HIGH);
    }
    if(option == 'j'){
      digitalWrite(ledDedoMenique, LOW);
    }
  }
}