/* Titan Encoderizado 
 *  
 *  Code by: Vinicius H. Schreiner
 * 
 */


#include <Encoder.h>

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKE 3
#define N_MOTORS 12
#define MOVE_SPD 255
#define BOLA 1
#define QUADRADO 2
#define TRIANGULO 3
#define XIS 4
#define pi 3.14159

int teste = true;
int rodada = 0;

//                                                                                
// PATA Bola - 1, 5, 9 | PATA Quadrado - 2, 6, 10 | PATA Triangulo - 3, 7, 11 | PATA Xis - 4, 8, 12   
//     motores = |  1|  2|  3|  4|  5|  6|  7|  8|  9| 10| 11|  12|;              
int inApin[12] = { 38, 25, 39, 24, 42, 29, 43, 28, 33, 31, 32, 30 }; // INA: Clockwise input
int inBpin[12] = { 44, 27, 45, 26, 40, 23, 41, 22, 35, 37, 34, 36 }; // INB: Counter-clockwise input
int pwmpin[12] = {  7,  8, 13,  2,  6,  9, 12,  3, 10, 11,  4,  5 }; // PWM input

bool target = false;
int direcao = 0;
int primeira = 0;
float erro = 5.0;
float upper_limit[3] = { 25 , 6, 8 };
float lower_limit[3] = { -25 , -6, -8 };

// Pinos para os encoders Bola
Encoder x1(A8, A15);
Encoder y1(A9, A14);
Encoder z1(A10, A13);

// Pinos para os encoders Quadrado

Encoder x2(A11, A12);
Encoder y2(A0, 53);
Encoder z2(A1, 51);

// Pinos para os encoders Triangulo

Encoder x3(A2, 49);
Encoder y3(A3, 47);
Encoder z3(A4, 46);

// Pinos para os encoders Xis

Encoder x4(A5, 48);
Encoder y4(A6, 50);
Encoder z4(A7, 52);

// Posicao anterior Bola

int pos_ant_x1 = 0;
int pos_ant_y1 = 0;
int pos_ant_z1 = 0;

// Posicao anterior Quadrado

int pos_ant_x2 = 0;
int pos_ant_y2 = 0;
int pos_ant_z2 = 0;

// Posicao anterior Triangulo

int pos_ant_x3 = 0;
int pos_ant_y3 = 0;
int pos_ant_z3 = 0;

// Posicao anterior Xis

int pos_ant_x4 = 0;
int pos_ant_y4 = 0;
int pos_ant_z4 = 0;

void setup()
{
  Serial.begin(9600);
  setupmotors();
}

void loop()
{
  //print_pos_enc_bola();
  //print_pos_enc_quadrado();
  //print_pos_enc_triangulo();
  //print_pos_enc_xis();
  testinho_bola();
  //testinho_quadrado();
  //testinho_triangulo();
  //testinho_xis();
  //testinho2(rodada);

/*
   motorGo(3, CCW, 20);
   motorGo(7, CCW, 20);
   motorGo(11, CCW, 20);
   delay(300);
   motorGo(3, CW, 20);
   motorGo(7, CW, 20);
   motorGo(11, CW, 20);
   delay(300);
*/
}
void inicia()
{
    motorGo(0, CCW, 150);
    motorGo(1, CW, 150);
    motorGo(2, CW, 150);
    primeira += 1;
}
void testinho_bola()
{
    
    if (z1.read() == 0)
    {
      motorGo(8, CCW,35);
    } else if (z1.read() <= -8)
    {
      motorGo(8, CW, 35);
    }

    
    if (x1.read() == 0)
    {
      motorGo(0, CCW, 40);
    } else if (x1.read() >= 8)
    {
      motorGo(0, CW, 50);
    }

    
    if (y1.read() == 0)
    {
      motorGo(4, CCW, 25);
    } else if (y1.read() <= -15)
    {
      motorGo(4, CW, 35);
    }
}

void testinho_quadrado()
{
    
    if (z2.read() == 0)
    {
      motorGo(9, CCW,35);
    } else if (z2.read() <= -8)
    {
      motorGo(9, CW, 35);
    }

    
    if (x2.read() == 0)
    {
      motorGo(1, CCW, 40);
    } else if (x2.read() <= 8)
    {
      motorGo(1, CW, 50);
    }

    
    if (y2.read() == 0)
    {
      motorGo(5, CCW, 25);
    } else if (y2.read() <= -8)
    {
      motorGo(5, CW, 25);
    }
}

void testinho_triangulo()
{
    
    if (z3.read() == 0)
    {
      motorGo(10, CCW,35);
    } else if (z3.read() <= -8)
    {
      motorGo(10, CW, 35);
    }

    
    if (x3.read() == 0)
    {
      motorGo(2, CCW, 40);
    } else if (x3.read() >= 8)
    {
      motorGo(2, CW, 50);
    }

    
    if (y3.read() == 0)
    {
      motorGo(6, CCW, 25);
    } else if (y3.read() <= -8)
    {
      motorGo(6, CW, 35);
    }
}

void testinho_xis()
{
    
    if (z4.read() == 0)
    {
      motorGo(11, CCW,35);
    } else if (z4.read() <= -8)
    {
      motorGo(11, CW, 35);
    }

    
    if (x4.read() == 0)
    {
      motorGo(3, CCW, 40);
    } else if (x4.read() >= 8)
    {
      motorGo(3, CW, 50);
    }

    
    if (y4.read() == 0)
    {
      motorGo(7, CCW, 25);
    } else if (y4.read() <= -8)
    {
      motorGo(7, CW, 25);
    }
}


void exibicao()
{
  //Serial.print("primeira: ");
  //Serial.println(primeira);
  if (primeira == 0)
  {
    motorGo(0, CCW, 150);
    motorGo(1, CW, 150);
    motorGo(2, CW, 150);
    primeira += 1;
  }
  else
  {
    //Serial.println("else exibicao");

    /*
    if (read_Angle(1) > 60)
    {
      motorGo(2, CCW, 25);
    } else if (read_Angle(1) < 30)
    {
      motorGo(2, CW, 25);
    }

    
    if (read_Angle(2) > 75)
    {
      motorGo(0, CW, 25);
    } else if (read_Angle(2) < 45)
    {
      motorGo(0, CCW, 25);
    }

    */
    if (x1.read() < 6)
    {
      motorGo(1, CCW, 25);
    } else if (z1.read() >= 6)
    {
      motorGo(1, CW, 25);
    }
    
    //Serial.println("final da exibição");
  }
}

float read_Angle(uint8_t numeroencoder)
{
  // função de leitura do ângulo
  float position_read = 0;
  float angle_variation = 90;
  float position_variation = (upper_limit[numeroencoder] - lower_limit[numeroencoder]);
  if (numeroencoder == 0)       // Primeira junta da pata
  {
    position_read = -y1.read();
  }
  else if (numeroencoder == 1)  // Segunda junta da pata
  {
    position_read = z1.read();
  }
  else if (numeroencoder == 2)  // Terceira junta da pata
  {
    position_read = -x1.read();
  }
  float scale = ( ( position_read - lower_limit[numeroencoder] ) / ( position_variation ) );
  float angle = (scale * angle_variation );
  if (pos_ant_x1 != x1.read() || pos_ant_y1 != y1.read() || pos_ant_z1 != z1.read())
  {
    //Serial.print("angulo: ");
    //Serial.println(angle);
  }
  return angle;
}

void moveTo( uint8_t motor, float goal)
{
  Serial.println("entrou funcao move to");
  target = false;
  float vel = MOVE_SPD;
  while (!target)
  {
    vel = vel - vel * 0.5;
    if (read_Angle( motor) > goal && vel > 0 )
    {
      motorGo(motor, CW, vel);
      Serial.print("CW: ");
      Serial.println(read_Angle( motor));
    }
    else if (read_Angle( motor) < goal && vel > 0)
    {
      motorGo(motor, CCW, vel);
      Serial.print("CCW: ");
      Serial.println(read_Angle( motor));
    }
    else
    {
      vel = 0;
      target == true;
      motorGo(motor, BRAKE, 0);
      Serial.println(vel);
      break;
    }
  }
}

void print_pos_enc_bola()
{
  pos_ant_x1 = x1.read();
  pos_ant_y1 = y1.read();
  pos_ant_z1 = z1.read();


  Serial.print("X1: ");
  Serial.print(x1.read());
  Serial.print("  Y1: ");
  Serial.print(y1.read());
  Serial.print("  Z1: ");
  Serial.println(z1.read());

  if (pos_ant_x1 != x1.read() || pos_ant_y1 != y1.read() || pos_ant_z1 != z1.read())
  {
    Serial.print("X1: ");
    Serial.print(x1.read());
    Serial.print("  Y1: ");
    Serial.print(y1.read());
    Serial.print("  Z1: ");
    Serial.println(z1.read());
  }
}

void print_pos_enc_quadrado()
{
  pos_ant_x2 = x2.read();
  pos_ant_y2 = y2.read();
  pos_ant_z2 = z2.read();


  Serial.print("X2: ");
  Serial.print(x2.read());
  Serial.print("  Y2: ");
  Serial.print(y2.read());
  Serial.print("  Z2: ");
  Serial.println(z2.read());

  if (pos_ant_x2 != x2.read() || pos_ant_y2 != y2.read() || pos_ant_z2 != z2.read())
  {
    Serial.print("X2: ");
    Serial.print(x2.read());
    Serial.print("  Y2: ");
    Serial.print(y2.read());
    Serial.print("  Z2: ");
    Serial.println(z2.read());
  }
}

void print_pos_enc_triangulo()
{
  pos_ant_x3 = x3.read();
  pos_ant_y3 = y3.read();
  pos_ant_z3 = z3.read();


  Serial.print("X3: ");
  Serial.print(x3.read());
  Serial.print("  Y3: ");
  Serial.print(y3.read());
  Serial.print("  Z3: ");
  Serial.println(z3.read());

  if (pos_ant_x3 != x3.read() || pos_ant_y3 != y3.read() || pos_ant_z3 != z3.read())
  {
    Serial.print("X3: ");
    Serial.print(x3.read());
    Serial.print("  Y3: ");
    Serial.print(y3.read());
    Serial.print("  Z3: ");
    Serial.println(z3.read());
  }
}

void print_pos_enc_xis()
{
  pos_ant_x4 = x4.read();
  pos_ant_y4 = y4.read();
  pos_ant_z4 = z4.read();


  Serial.print("X4: ");
  Serial.print(x4.read());
  Serial.print("  Y4: ");
  Serial.print(y4.read());
  Serial.print("  Z4: ");
  Serial.println(z4.read());

  if (pos_ant_x4 != x4.read() || pos_ant_y4 != y4.read() || pos_ant_z4 != z4.read())
  {
    Serial.print("X4: ");
    Serial.print(x4.read());
    Serial.print("  Y4: ");
    Serial.print(y4.read());
    Serial.print("  Z4: ");
    Serial.println(z4.read());
  }
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  // função para movimentação do motor
  // entra com número do motor, sentido de rotação e PWM de acionamento do motor
  if (motor <= N_MOTORS)
  {
    if (direct <= 4)
    {
      // Set inA[motor]
      if (direct <= 1 )
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);
      // Set inB[motor]
      if ((direct == 0) || (direct == 2) )
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);
      analogWrite(pwmpin[motor], pwm);
    }
  }
}

//  = = = = = = = = = = = = = = = INICIALIZAÇÃO DOS MOTORES = = = = = = = = = = = = = = =
void setupmotors()
{
  // SETUP DOS MOTORES
  for (int i = 0; i < N_MOTORS; i++)
  {
    // Seta os pinos dos motores como saida
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
    // Começa com os motores parados
    motorOff(N_MOTORS);
  }
}

void motorOff(int motor)
{
  // DESLIGA TODOS OS MOTORES
  for (int i = 0; i < N_MOTORS; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], BRAKEVCC);
}

//  = = = = = = = = = = = = = = = FUNÇÕES DE CINEMÁTICA INVERSA (MODELO 1) = = = = = = = = = = = = = = =
void CODIGO_M1(float tetinha2)
{
  motorGo(1, CCW, 0);
  motorGo(1, CW, 0);
  while (read_Angle(0) <= tetinha2)
  {
    Serial.print("While 1: ");
    Serial.println(read_Angle(0));  // varia de 50 a 75 do pot 1
    motorGo(1, CCW, 255);              // sobe o motor 2
  }
  while (read_Angle(0) > tetinha2)
  {
    Serial.print("While 2: ");
    Serial.println(read_Angle(0));  // varia de 50 a 75 do pot 1
    motorGo(1, CW, 255);             // sobe o motor 2
  }
  motorGo(1, CCW, 0);
  motorGo(1, CW, 0);
}

void CODIGO_M0(float tetinha3)
{
  motorGo(0, CCW, 0);
  motorGo(0, CW, 0);
  while (read_Angle(2) >= tetinha3)
  {
    Serial.print("While 1: ");
    Serial.println(read_Angle(2));  // varia de 50 a 75 do pot 1
    motorGo(0, CCW, 255);              // sobe o motor 2
  }
  while (read_Angle(2) < tetinha3)
  {
    Serial.print("While 2: ");
    Serial.println(read_Angle(2));  // varia de 50 a 75 do pot 1
    motorGo(0, CW, 255);             // sobe o motor 2
  }
  motorGo(0, CCW, 0);
  motorGo(0, CW, 0);
}

void CI2(float X, float Z)
{
  //cinematica inversa igual ao relatorio
  float alfa = 0, beta = 0, gama = 0, RX = 0, RZ = 0, R = 0, teta2 = 0, teta3 = 0, t2 = 0, t3 = 0;

  RX = X + 4.5;
  RZ = Z - 6.5;
  R = sqrt((RX * RX) + (RZ * RZ));
  Serial.print("R: ");
  Serial.println(R);
  beta = acos((640.25 - (R * R)) / (620));  // equação 4.2
  Serial.print("Beta: ");
  Serial.println(beta);
  alfa = acos(((R * R) - 159.75) / (31 * R)); // equação 4.4
  Serial.print("Alfa: ");
  Serial.println(alfa);
  gama = atan2(RZ, RX);
  Serial.print("Gama: ");
  Serial.println(gama);
  teta2 = (alfa + gama);  //equação 4.5
  Serial.print("Teta 2: ");
  Serial.println(teta2);
  teta3 = pi - teta2 - beta;  // equação 4.6
  Serial.print("Teta 3: ");
  Serial.println(teta3);
  Serial.print("Teta 2 graus: ");
  Serial.println((teta2 * (180 / pi)));
  Serial.print("Teta 3 graus: ");
  Serial.println((teta3 * (180 / pi)));
  Serial.print("Teta 2 grau -45: ");
  t2 = (teta2 * (180 / pi)) - 45;
  Serial.println(t2);
  Serial.print("Teta 3 grau +45: ");
  t3 = (teta3 * (180 / pi)) + 45;
  Serial.println(t3);
  CODIGO_M0(t2);
  CODIGO_M1(t3);
}
