#define DS_pin 6
#define STCP_pin 5
#define SHCP_pin 4

#define ship 0
#define enemy 1
#define muerte 2
 
int randomCounter=0;
int respuesta=0; 

int posX=0;
int posY=0;
int posZ=0;

int posXE=0;
int posYE=0;
int posZE=0;



int Arreglo[16];
int Botones[7]={0,0,0,0,0,0,0};
int perdedor[6]={0,0,0,0,0,0};
int contador=0;

int Matrix[3][4][4][4]=
{
  {
    {
      {1,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    } 
  },
  {
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },
  {
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  }
};

void setup()
{
  randomSeed(analogRead(0));
  posXE=random(1,4);
  posYE=random(0,4);
  posZE=random(0,4);
  Matrix[enemy][posZE][posYE][posXE]=1;
  for(int i=0; i<7;i++){
    pinMode(i, OUTPUT);
  }
  for(int i=7; i<14; i++){
    pinMode(i, INPUT);
  }
}

void ShiftRegister(){
  digitalWrite(STCP_pin, LOW);
    for(int i=15; i>=0; i--){
      digitalWrite(SHCP_pin, LOW);
        digitalWrite(DS_pin, Arreglo[i]);
        digitalWrite(SHCP_pin, HIGH);
    }
    digitalWrite(STCP_pin, HIGH);
}

void MoverPos(int i){
  switch(i){
    case 8:posX--;
          break;
  case 7: posY++;
          break;
  case 10:posY--;
          break;
  case 9: posX++;
          break;
  case 12: posZ--;
          break;
  case 11: posZ++;
        break;
  }
  posX = constrain(posX,0,3);
  posY = constrain(posY,0,3);
  posZ = constrain(posZ,0,3);
}

void MoverPosEnemy(int i){
  switch(i){
    case 8:posXE--;
          break;
  case 7: posYE++;
          break;
  case 10:posYE--;
          break;
  case 9: posXE++;
          break;
  case 12: posZE--;
          break;
  case 11: posZE++;
        break;
  }
  posXE = constrain(posXE,0,3);
  posYE = constrain(posYE,0,3);
  posZE = constrain(posZE,0,3);
}

void Mover(){
  
  for(int i=13; i>=7; i--){
    if(digitalRead(i)==HIGH && Botones[13-i]==0){
      Botones[13-i]=!Botones[13-i];
        MoverPos(i);
    }
    if(digitalRead(i)==LOW && Botones[13-i]==1)
      Botones[13-i]=!Botones[13-i];
  }
}

void colision(){
  
  Matrix[muerte][posZ][posY][posX]=1;
 
  perdedor[0]=posX-1;
  perdedor[1]=posY-1;
  perdedor[2]=posZ-1;
  perdedor[3]=posX+1;
  perdedor[4]=posY+1;
  perdedor[5]=posZ+1;
  

    for(int i=0; i<9; i++){
        perdedor[i]=constrain(perdedor[i],0,3);
    }
    
    for(int k=perdedor[2]; k<=perdedor[5]; k++){
      for(int i=perdedor[0]; i<=perdedor[3]; i++){
        for(int j=perdedor[0]; j<=perdedor[3]; j++){
          Matrix[muerte][k][i][j]=1;    
        }
      }    
    }
  
 for(int scan=0; scan<5; scan++){ 
    int barrido=0;
    do{
      barrido++;
      for(int Nivel=0; Nivel<4; Nivel++){
        for(int i=0; i<4; i++)
          for(int j=0; j<4; j++){
            Arreglo[contador]=Matrix[muerte][Nivel][i][j];
            contador++;
          }
        ShiftRegister();
        digitalWrite(Nivel, LOW);
        limpiar(Nivel);
      }
      ShiftRegister();
    }while(barrido<300);
 }

  for(int Nivel=0; Nivel<4; Nivel++)
    for(int i=0; i<4; i++)
      for(int j=0; j<4; j++)
        Matrix[muerte][Nivel][i][j]=0;
}


void limpiar(int Nivel){
    contador=0;
    for(int x=0; x<16;x++)
      Arreglo[x]=0;
    ShiftRegister();
    digitalWrite(Nivel, HIGH);
}


void limpiar3D(){
  for(int z=0; z<4; z++)
    for(int x=0; x<4; x++)
      for(int y=0; y<4; y++){
        Matrix[ship][z][x][y]=0;
        Matrix[enemy][z][x][y]=0;
      }     
}

void reiniciarJuego(){
  posX=posY=posZ=0;
  for(int i=0; i<9; i++)
      perdedor[i]=0;
  limpiar3D();
  Matrix[ship][posZ][posY][posX]=1;
  Matrix[enemy][posZE][posYE][posXE]=1; 
  
}

void moverEnemigo(){
    if(randomCounter == 2){
      respuesta = random(0,16);
      randomCounter=0;
      }
      MoverPosEnemy(respuesta);
      randomCounter++;
  }
void loop()
{
  for(int scan=0; scan<100; scan++){
    for(int Nivel=0; Nivel<4; Nivel++){
      for(int i=0; i<4; i++)
        for(int j=0; j<4; j++){

          if(Matrix[enemy][Nivel][i][j]==1 && Matrix[ship][Nivel][i][j]==1){
            colision();
            delay(100);
            reiniciarJuego();
            }

          if(Matrix[enemy][Nivel][i][j] == 1){  
            Arreglo[contador]= 1;
          }
          else if(Matrix[ship][Nivel][i][j] == 1){
            Arreglo[contador]= 1;
            }
          else{
            Arreglo[contador]= 0;
            }  
            contador++;   
        }
      ShiftRegister();
      digitalWrite(Nivel, LOW);
      limpiar(Nivel);
    }
  }
  moverEnemigo();  
  Mover();
  limpiar3D();
  Matrix[ship][posZ][posY][posX]=1;
  Matrix[enemy][posZE][posYE][posXE]=1;
}
