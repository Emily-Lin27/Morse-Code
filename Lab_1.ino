// Link to morse code symbols: http://morsecode.scphillips.com/morse2.html
// Link to references: energia.nu/reference

/*
 * Name: Emiy Lin
 * Student ID: 20669423
 * Description: Converts user input (26 letters) into morse code. Ignores puncutation and multiple spaces.
 */

#define LED GREEN_LED

char input[5000]; // stores user input

// stores the morse code sequence
String morse[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.","...", "-", "..-", "...-", ".--","-..-","-.--","--.."};

boolean hadSpace = true;  // keeps track of consecutive spaces
const int waitTime = 4000;

void setup () { 
  Serial.begin(9600); 
  pinMode(LED, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    Serial.readBytesUntil(10, input, sizeof(input)); // reads input from user until newline char is reached

    for (int i = 0; input[i] != '\0' && i < sizeof(input); i++){  // reads individual letters 
      if (input[i] == 32 && hadSpace ==  true){  // if have multiple spaces
        continue; 
      }
      
       hadSpace = false;
       
      if (input[i] == 32){ // if it is a space
        hadSpace = true;
        delay(waitTime); // accounts for 1s wait between chars and 3 second wait between letters 
      } else {
         hadSpace = false; 
   
         if (input[i] > 96 && input[i] < 123){ // if lowercase
             readChar(input[i] - 97);           
             delay(waitTime/2); //delays for appropriate amount of time (already have 1s wait in the function)
         } else { // if uppercase
            if (input[i] > 64 && input[i] < 91) {
               readChar(input[i] - 65); 
               delay(waitTime/2); //delays for appropriate amount of time (already have 1s wait in the function)
            }
          }
        }
        input[i] = '\0'; 
      }
    }
 }

void readChar(int num){ // Reads each character   
   for (int i = 0; i < morse[num].length(); i++){
       if (morse[num].charAt(i) == '.'){
          digitalWrite(LED, HIGH);
          delay(waitTime/4);  // leaves LED on for 1 second
       } else {
          digitalWrite(LED, HIGH); 
          delay(3000);  // leaves LED on for 3 seconds 
       }
       digitalWrite(LED, LOW); 
       delay(waitTime/4); // One dot length wait between dots and dashes
   }
}

