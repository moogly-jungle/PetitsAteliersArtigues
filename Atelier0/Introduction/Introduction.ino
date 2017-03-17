#include <Servo.h>

#define PIN_POTENTIOMETRE 0
int commande;

#define PIN_MOTEUR 4
Servo moteur;
int angle;

void setup() {
  Serial.begin(9600);
  moteur.attach(PIN_MOTEUR);
}

void loop() {
  /* lecture du potentiometre : valeur dans [0,1023] */
  commande = analogRead(PIN_POTENTIOMETRE);
  /* retour dans le terminal (ouvrir outil/moniteur série) */
  Serial.print("commande = "); Serial.print(commande); Serial.print(" ; ");

  /* sortie dans le buzzer branché sur le pin 3, avec le bouton pour couper le son ... */
  tone(3, 440 + commande);

  /* pilotage du servo-moteur
   * <Attention> le potentiometre prend sa tension de ref sur l'arduino et le servo sur la batterie
   * sinon, le servo perturbe la tension de référence du potentiomètre */
  angle = map(commande, 0, 1023, 0, 180); /* transforme la commande de [0,1023] -> [0,180] */
  moteur.write(angle); 
  Serial.print("angle = "); Serial.print(angle); Serial.print("\n");

  /* pilotage de la led */
  int blue = map(commande, 0, 1023, 0, 255); /* transforme la commande de [0,1023] -> [0,255] */
  analogWrite(5, blue);
}
