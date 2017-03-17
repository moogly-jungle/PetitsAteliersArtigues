#include <Servo.h>

/* --------------
 *  Introduction
 * --------------
 * Introduction rapide à l'Arduino Uno
 * 1) Commencer par brancher le moteur et envoyer des valeurs constantes
 *    - le moteur, c'est motivant, ça sort un peu de l'ordinaire, et c'est lié à la robotique
 *    - il faut introduire le concept d'angle pour les petits
 * 1' option) faire une boucle avec un délai pour faire bouger le servo "tout seul"
 *    - c'est l'occasion de parler de variable, et de boucle (ne pas oublier le délai)
 * 1'' option) monitorer le signal à l'oscilloscope
 * 2) Brancher le potentiomètre, faire un retour dans le terminal pour voir concretement bouger la valeur
 * 3) Piloter le servo avec le potentiomètre, on introduit map
 * 4) Brancher et tester le buzzer avec le bouton poussoir (ce sera infernal sinon...)
 * 5) Piloter le buzzer en modifiant la frequence avec le potentiomètre
 * 6) Brancher, tester la led RGB, puis la piloter avec le potentiomètre.
 */

#define PIN_POTENTIOMETRE 0 /* brancher le potentiomètre sur A0 (Analog In sur la gauche de la carte) */
int commande;

#define PIN_MOTEUR 4
Servo moteur;
int angle;

void setup() {
  Serial.begin(9600);
  moteur.attach(PIN_MOTEUR);

  /* option : pour montrer le concept de mouvement,
   * on fait varier le délai pour faire varier la vitesse */
  for (angle=0; angle<180; angle = angle+1) { /* angle = angle+1 plutot que angle++ pour simplifier la syntaxe */
    moteur.write(angle); /* on évite les float, pour les élèves de primaire, c'est un peu complexe */
    delay(20);
  }
  for (angle=180; angle>0; angle = angle-1) {
    moteur.write(angle);
    delay(20);
  }
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
  // moteur.write(angle); 
  Serial.print("angle = "); Serial.print(angle); Serial.print("\n");

  /* pilotage de la led */
  int blue = map(commande, 0, 1023, 0, 255); /* transforme la commande de [0,1023] -> [0,255] */
  analogWrite(5, blue);
}
