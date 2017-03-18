#include <Servo.h>

/* --------------
 *  Introduction
 * --------------
 * Introduction rapide à l'Arduino Uno
 * 1) Commencer par brancher le moteur et envoyer des valeurs constantes
 *    - le cablage du moteur : maron ou noir : GND / rouge : Vcc batterie / orange ou jaune : signal (sur le pin 4)
 *    - le moteur, c'est motivant, ça sort un peu de l'ordinaire, et c'est lié à la robotique
 *    - il faut introduire le concept d'angle pour les petits
 * 1' option) faire une boucle avec un délai pour faire bouger le servo "tout seul"
 *    - c'est l'occasion de parler de variable, et de boucle (ne pas oublier le délai)
 * 1'' option) monitorer le signal à l'oscilloscope (démonstration)
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
  Serial.begin(9600); /* pas vraiment d'explication sur ça, c'est trop compliqué pour les petits */
  moteur.attach(PIN_MOTEUR);

  /* option : pour montrer le concept de mouvement,
   * on fait varier le délai pour faire varier la vitesse */
  Serial.println();
  Serial.print("Mise en marche du moteur ... ");
  angle=0;
  while (angle<180) { /* while est plus comprehensible pour le début */
    moteur.write(angle); /* on évite les float, pour les élèves de primaire, c'est un peu complexe */
    angle = angle+1; /* angle = angle+1 plutot que angle++ pour simplifier la syntaxe */
    delay(20);
  }
  while (angle>0) { /* while est plus comprehensible pour le début */
    moteur.write(angle); /* on évite les float, pour les élèves de primaire, c'est un peu complexe */
    angle = angle-1; /* angle = angle+1 plutot que angle++ pour simplifier la syntaxe */
    delay(20);
  }
  Serial.println("ok !");
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
  Serial.print("angle = "); Serial.println(angle); 

  /* pilotage de la led */
  int blue = map(commande, 0, 1023, 0, 255); /* transforme la commande de [0,1023] -> [0,255] */
  analogWrite(5, blue);
}
