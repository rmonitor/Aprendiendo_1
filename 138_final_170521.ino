/* Este programa cuenta los carros subidos con la plataforma, bien sean carros sueltos u un carro grande, y lo muestra en el display de un GPS específico, solo emite una señal de salida siempre y cuando se cumpla:
Las presencias y el pison (plataforma) han sido activados mas de 1.5 segundos, si la plataforma esta activa no hace nada.
3 señales presenciales y una de plataforma, con las presenciales podemos contar unitariamente, en conjunto o si es un carro grande que esten presentes las 3 señales y la plataforma
*/
#include <EEPROM.h>   
const char STX = '\x02';            // variable necesaria para mostrado (comienzo) en GCD17 
const char ETX = '\x03';            // variable necesaria para mostrado (fin) en GCD17

//presencias
int presencia_1 = 2;                // sensor de presencia 1
int salida_presencia_1 = 10;         // salida de sensor presencia a led 

int presencia_2 = 3;                // sensor de presencia 2
int salida_presencia_2 = 7;         // salida de sensor presencia a led 

int presencia_media = 4;                // sensor de presencia media
int salida_presencia_media = 8;         // salida de sensor presencia a led 

//temporizaciones
unsigned long T_inicio_puls_pres_1 = 0;          // inicio a 0
unsigned long T_inicio_puls_pres_2 = 0;          // inicio a 0
unsigned long T_inicio_puls_pres_media = 0;      // inicio a 0
unsigned long T_inicio_puls_pison = 0;           // inicio a 0
unsigned long T_pulsado_1;                       // tiempo para cálculo antirebote y de presencia 
unsigned long T_pulsado_2;                       // tiempo para cálculo antirebote y de presencia
unsigned long T_pulsado_media;                   // tiempo para cálculo antirebote y de presencia
unsigned long T_pulsado_pison;                   // tiempo para cálculo antirebote y de presencia

//pison    
int pison = 5;                                  // sensor de plataforma 
int salida_pison = 9;                           // salida de sensor cierre a led  


// Variables

int variable_salida_presencia_1 = 0 ;
int estado_presencia_1;                     // variable de la presencia
int variable_salida_presencia_2 = 0 ;
int estado_presencia_2;                       // variable de la presencia
int variable_salida_presencia_media = 0 ;
int estado_presencia_media;                   // variable de la presencia
int variable_salida_pison = 0;
int estado_pison;                                 // variable de la plataforma
int variable_gps_3 = 0;                         // cambiará cuando la presencia_1, presencia_2 y el pison esten en 1
int variable_gps_1 = 0;
int estado_anterior_variable_gps_1 = LOW;
int variable_gps_2 = 0;
int estado_anterior_variable_gps_2 = LOW;
int estado_anterior_variable_media = LOW;

//gps
int salida_gps = 6;                         // asigno salida 7 hacia el guarda
int contador_cubo_1 = 0;                    // contador cubos lado izq
int contador_cubo_2 = 0;                    // contador cubos lado derch
int contador_2_cubos = 0;                   // contador cuando se elevan 2 cubos a la vez
int contador_contenedor = 0;                // contador contenedor
int contador_ele = 0;                       // contador general de elevaciones
char cadena[] = "Acumulado - ";             // cadena de texto que muestra en GPS

void setup() {
  Serial.begin(9600);                        // inicializo puerto serie
  //presencias
  pinMode(presencia_1, INPUT);               // El presencia_1 será entrada de sensor.
  pinMode(salida_presencia_1, OUTPUT);       // El salida_presencia_1 será salida hacia LED
  pinMode(presencia_2, INPUT);               // El presencia_2 será entrada de sensor.
  pinMode(salida_presencia_2, OUTPUT);       // El salida_presencia_2 será salida hacia LED
  pinMode(presencia_media, INPUT);            // El presencia_media será entrada de sensor central.
  pinMode(salida_presencia_media, OUTPUT);    // El salida_presencia_media será salida hacia LED
  //pison  
  pinMode(pison, INPUT);                      // El pison será entrada pulsador.
  pinMode(salida_pison, OUTPUT);              // El salida_pison será salida led.
  //gps
  pinMode(salida_gps, OUTPUT);                // El salida_gps será salida hacia gps
                }

void loop() {
  // tratado de la presencia 1//
  if (estado_pison == HIGH) {} else {                                                                                    //si el pison esta activo no se hace nada
   estado_presencia_1 = digitalRead(presencia_1);                                                                        //asigna el estado de la presencia a la variable
  if (estado_presencia_1 == HIGH & T_inicio_puls_pres_1 == 0)                                                            //compara si esta en 1 y el tiempo pulsado sigue a 0
      {T_inicio_puls_pres_1 = millis();}                                                                                 //inicializo el tiempo pulsado con el tiempo maquina
   T_pulsado_1 = millis() - T_inicio_puls_pres_1;                                                                        //tiempo de pulsado 
  if ( T_pulsado_1 >= 150 & estado_presencia_1 == LOW) T_inicio_puls_pres_1=0 ;                                          //evito rebote
  if (T_inicio_puls_pres_1 != 0)                                                                                         //
      {if (T_pulsado_1 >= 1500){digitalWrite(salida_presencia_1, HIGH);variable_salida_presencia_1 = 1;} }               //si el tiempo de pulsado es superior a 1,5s enciende el led y su variable la pone a 1
      else {digitalWrite(salida_presencia_1, LOW);variable_salida_presencia_1 = 0;}}
    
    // tratado de la presencia 2//
  if (estado_pison == HIGH) {} else { //si el pison esta activo no se hace nada
   estado_presencia_2 = digitalRead(presencia_2);                                                                        //asigna el estado de la presencia a la variable
  if (estado_presencia_2 == HIGH & T_inicio_puls_pres_2 == 0)                                                            //compara si esta en 1 y el tiempo pulsado sigue a 0
      {T_inicio_puls_pres_2 = millis();}                                                                                 //inicializo el tiempo pulsado con el tiempo maquina
   T_pulsado_2 = millis() - T_inicio_puls_pres_2;                                                                        //tiempo de pulsado 
  if (T_pulsado_2 >= 150 & estado_presencia_2 == LOW) T_inicio_puls_pres_2=0 ;                                           //evito rebote
  if (T_inicio_puls_pres_2 != 0)
      {if (T_pulsado_2 >= 1500){digitalWrite(salida_presencia_2, HIGH);variable_salida_presencia_2 = 1;} }               //si el tiempo de pulsado es superior a 1,5s enciende el led y su variable la pone a 1
      else {digitalWrite(salida_presencia_2, LOW);variable_salida_presencia_2 = 0;}}
    
   // tratado de la media//
  if (estado_pison == HIGH) {} else {
   estado_presencia_media = digitalRead(presencia_media);                         
  if (estado_presencia_media == HIGH & T_inicio_puls_pres_media == 0)            
      {T_inicio_puls_pres_media = millis();}                                     
   T_pulsado_media = millis() - T_inicio_puls_pres_media;
  if (T_pulsado_media >= 150 & estado_presencia_media == LOW) T_inicio_puls_pres_media=0 ;  
  if (T_inicio_puls_pres_media != 0)
      {if (T_pulsado_media >= 1500){digitalWrite(salida_presencia_media, HIGH);variable_salida_presencia_media = 1; } } 
      else {digitalWrite(salida_presencia_media, LOW);variable_salida_presencia_media = 0;}}    
             
  // tratado del pison//
   estado_pison = digitalRead(pison);                         
  if (estado_pison == HIGH & T_inicio_puls_pison == 0)             
      {T_inicio_puls_pison = millis();}                                    
   T_pulsado_pison = millis() - T_inicio_puls_pison;
  if (T_pulsado_pison >= 150 & estado_pison == LOW) T_inicio_puls_pison=0;
  if (T_inicio_puls_pison != 0)
      {if (millis() - T_inicio_puls_pison >= 1500){digitalWrite(salida_pison, HIGH); variable_salida_pison = 1;} } 
      else {digitalWrite(salida_pison, LOW);variable_salida_pison = 0;}
    
  //Tratado de la salida gps
  if (variable_gps_1 = (variable_salida_presencia_1 == 1  &  variable_salida_pison == 1 )) { estado_anterior_variable_gps_1 = HIGH; T_inicio_puls_pres_2 = millis() ;} 
  if (estado_presencia_1 == LOW & estado_pison == LOW & estado_anterior_variable_gps_1 == HIGH  ) 
    {salida_gps1();} else {digitalWrite(salida_gps, LOW);}     
  if (variable_gps_2 = (variable_salida_presencia_2 == 1  &  variable_salida_pison == 1 )) { estado_anterior_variable_gps_2 = HIGH; T_inicio_puls_pres_1 = millis(); }
  if (estado_presencia_2 == LOW & estado_pison == LOW & estado_anterior_variable_gps_2 == HIGH  )  
    {salida_gps1();} else {digitalWrite(salida_gps, LOW);}
  if (variable_salida_presencia_media == 1  &  variable_salida_presencia_1 == 1 &  variable_salida_presencia_2 == 1) {estado_anterior_variable_media = HIGH;}
  if (estado_presencia_media == LOW & estado_pison == LOW & estado_anterior_variable_media == HIGH  )  
    {salida_gps1();} else {digitalWrite(salida_gps, LOW);}    

   //EEPROM.put(0, 0); Serial.print ("Acum.Anterior - ");Serial.println( EEPROM.get(0, contador_ele) );               // solo para inicializar, ponemos a 0 el contador general en la posición 0
   //EEPROM.put(10, cadena); Serial.println( EEPROM.get(10, cadena) );                                                //escribimos la cadena en posicion 10
      }

  // Subrutina salida gps.
  void salida_gps1(){
     Serial.print(STX);
     Serial.print ("Acum.Anterior - ");Serial.println( EEPROM.get(0, contador_ele) );
      digitalWrite(salida_gps, HIGH);
  if (digitalRead(salida_gps) == HIGH){                                                                               // comprueba que la salida este en alto
      contador_ele++;                                                                                                 // aumenta 1 si salida en alto
  if (estado_anterior_variable_media == HIGH ) 
      {Serial.print("Contenedor - ");contador_contenedor++;Serial.println(contador_contenedor);}  else 
  if (estado_anterior_variable_gps_1 == HIGH & estado_anterior_variable_gps_2 == HIGH ) 
      {Serial.print("2 cubos - ");contador_2_cubos++;contador_2_cubos++;Serial.println(contador_2_cubos);}  else          
  if (variable_gps_1 == LOW & estado_anterior_variable_gps_1 == HIGH )
      {Serial.print("cubo izq - ");contador_cubo_1++; Serial.println(contador_cubo_1);}   else                        // muestra el número de envios  
  if (variable_gps_2 == LOW & estado_anterior_variable_gps_2 == HIGH )
      {Serial.print("cubo drch - ");contador_cubo_2++;Serial.println(contador_cubo_2);}                               // muestra el número de envios   
         
  if (EEPROM.read (0) <= contador_ele) {EEPROM.put(0, contador_ele++); }
    Serial.print( EEPROM.get(10, cadena) );
    Serial.println( EEPROM.get(0, contador_ele) );  
    Serial.print(ETX);
                                }                                          
   delay(25);                                
  estado_anterior_variable_gps_1 = LOW;    
  estado_anterior_variable_gps_2 = LOW;      
  variable_salida_presencia_media = LOW;
  variable_salida_presencia_1 = 0 ;
  variable_salida_presencia_2 = 0 ;
  variable_salida_pison = 0;    
  variable_gps_3 = 0;                   
  variable_gps_1 = 0;
  variable_gps_2 = 0;
  estado_anterior_variable_media = LOW; 
  
      }
    
