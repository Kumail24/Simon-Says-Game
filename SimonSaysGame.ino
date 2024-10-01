#define MAX_ROUND 10

int buttonPin[] = {2, 3, 4, 5};
int ledPin[] = {6, 7, 8, 9};

int gameSequence[MAX_ROUND];
int userSequence[MAX_ROUND];
int currentRound = 0;
  
void setup()
{
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
    pinMode(ledPin[i], OUTPUT);    
  }
  randomSeed(analogRead(A0));
  
  Serial.begin(9600);
}

int userInput() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPin[i]) == LOW) {
      return i;
    }   
  }
  return -1;
}

bool checkUserInput() {
  for (int i = 0; i <= currentRound; i++) {
    if (userSequence[i] != gameSequence[i]) {
      for (int j = 0; j < 4; j++) {
        //displays incorrect input to user
      	digitalWrite(ledPin[ userSequence[i] ], HIGH);
      	delay(250);
      	digitalWrite(ledPin[ userSequence[i] ], LOW);
      	delay(250);
      }  
      return false;
    }
  }
  return true;
}

void getSequence(int i) {  
  digitalWrite(ledPin[gameSequence[i]], HIGH);
  delay(400);
  digitalWrite(ledPin[gameSequence[i]], LOW);
  delay(400);
}

void loop() {
  
  if (currentRound == MAX_ROUND) {
    currentRound = 0;
    Serial.print("You Win!\nRestarting game...\n");
  }
  
  gameSequence[currentRound] = random(0, 4);
    
  for (int i = 0; i <= currentRound; i++) {
    //lights up leds in gameSequence's order
    getSequence(i);	
  }
  
  Serial.print("Current Round: " + String(currentRound) + "\n");
  Serial.print("New LED: " + String(gameSequence[currentRound]) + "\n");
  
  for (int i = 0; i <= currentRound; i++) {    
    int button;
    
  	do {
  		button = userInput();
    	delay(10);
  	} while (button == -1);
    
    userSequence[i] = button;
    Serial.print("User pressed: ");
    Serial.print(userSequence[i]);
    Serial.print("\n");
    
    digitalWrite(ledPin[button], HIGH);
    delay(400);
    digitalWrite(ledPin[button], LOW);
  }
  
  if(!checkUserInput()) {
    Serial.print("Game Over!\n");
    currentRound =0;    
    delay(1000);
    return;
  }
  
  //round win animation
  delay(400);
  digitalWrite(ledPin[0], HIGH);
  digitalWrite(ledPin[1], HIGH);
  digitalWrite(ledPin[2], HIGH);
  digitalWrite(ledPin[3], HIGH);
  delay(400);
  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW);
  digitalWrite(ledPin[3], LOW);
  
  currentRound++;
  delay(1000);
}
