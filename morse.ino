
int speakerPin = D3;
int greenLED = A1;
int redLED = A3;
int redSwitch = D5;
int greenSwitch = D4;
int note = 550;
int dotLen = 100;
int dashLen = 3*dotLen;
int spaceLen = 7*dotLen;
String lastMessage = "";
boolean searching = false;

const String morse[] = { ".-", "-...", "-.-.", "-..",
  ".","..-.","--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
  ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
  "--.."};

void setup() {
pinMode(greenSwitch,INPUT_PULLUP); // enable the green switch
pinMode(redSwitch,INPUT_PULLUP); // enable the red switch
pinMode(speakerPin, OUTPUT);
pinMode(redLED, OUTPUT);
Serial.begin(9600);
Particle.function("morseMe",saveText);
Particle.function("playSOS",playSOS);
Particle.function("findMyPhoton",findPhoton);
}

void loop() {
  if (searching){
      convertMorse("SOS");
  }
  if(digitalRead(redSwitch) == LOW) {
      Serial.println("Red Switch Pressed");
      searching = false;

  }
  if(digitalRead(greenSwitch) == LOW) {
      Serial.println("Green Switch Pressed");
      convertMorse(lastMessage);
  }
}

int playSOS(String msg){
    convertMorse(msg);
    return 1;
}

int findPhoton(String findme){
    searching = true;
    return 1;
}

int saveText(String message){
  lastMessage = message;
  convertMorse(lastMessage);
  return 1;
}

void convertMorse(String message){
    int i = 0; //count variable
  char C; //holds each letter
  while (message[i]) {
    C = toupper(message[i]);
    if (C>=65 && C<=90) {
      signalMorse(morse[C-65]);
       Serial.print(morse[C-65]);
    }
    i++; // move to the next char
  }
  Serial.println();
}

void signalMorse(String c) {
  int i = 0;
  while (c[i]) {
    digitalWrite(redLED,HIGH); // Turn On LED
    tone(speakerPin, note); // Buzz the Speaker
    if (c[i] == '.') {
       delay(dotLen);  // delay for dot secs
    } else if (c[i] == '-') {
       delay(dashLen); //delay for dash secs
    }
    digitalWrite(redLED,LOW); // Turn off LED
    noTone(speakerPin); // Buzz off Speaker
    delay(dotLen); //
    i++;
  };

}
