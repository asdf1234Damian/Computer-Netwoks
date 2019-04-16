#include <stdio.h>
#include <stdlib.h>
unsigned char tramas[][30]={
{0x05,0xca,0xCF,0xdb,0x48,0x48,0x69,0x21},//0 Hi! bit (!par)
{0x05,0xcb,0xCF,0xdb,0x48,0x48,0x69,0x21},//1 Hi! bit (par)
{0x05,0xc6,0xCF,0xdb,0x48,0x48,0x69,0x21},//2 Hi! CheckSum
{0x05,0xc2,0xCF,0xdb,0x98,0x42,0x6f,0x6e,0x6a,0x6f,0x75,0x72,0x00,0x00,0x00},//3 Bonjour CRC_8 (blanco)
{0x05,0xc2,0xCF,0xdb,0x98,0x42,0x6f,0x6e,0x6a,0x6f,0x75,0x72,0x00,0x00,0xc9},//4 Bonjour CRC_8 (bien)
{0x05,0xce,0xCF,0xdb,0x98,0x42,0x6f,0x6e,0x6a,0x6f,0x75,0x72,0x00,0x00,0x00,0x00,0x00,0x00},// Bonjour CRC_32 (blanco)
{0x05,0xce,0xCF,0xdb,0x98,0x42,0x6f,0x6e,0x6a,0x6f,0x75,0x72,0x00,0x00,0xff,0xb4,0x2c,0x80 },// Bonjour CRC_32 (blanco)
{0x05,0xc6,0xCF,0xdb,0x98,0x42,0x6f,0x6e,0x6a,0x6f,0x75,0x72},// Bonjour Check (crear)
{0x05,0xce,0xCF,0xdb,0xf0,0x4d,0x69,0x20,0x74,0x72,0x61,0x6d,0x61,0x20,0x71,0x75,0x65,0x64,0x6f,0x20,0x3d,0x29},// Mi trama quedo
{0x05,0xce,0xCF,0xdb,0xf0,0x4d,0x69,0x20,0x74,0x72,0x61,0x6d,0x61,0x20,0x71,0x75,0x65,0x64,0x6f,0x20,0x3d,0x29,0x00,0xf3,0x40,0x9c,0x27 },
// // Ejercicio de clase:
{0x05,0xc2,0xCF,0xdb,0x48,0x44,0x61,0x6e, 0x00}, // CRC 8
{0x05,0xc2,0xCF,0xdb,0x48,0x44,0x61,0x6e, 0x93}, // CRC 8
{0x05,0xce,0xCF,0xdb,0x98,0xf0,0x00,0x00,0x00,0x00}, // CRC 32
{0x05,0xce,0xCF,0xdb,0x98,0xf0,0x07,0x3a,0x7b,0x9d}, // CRC 32
{0x05,0xc2,0xCF,0xdb,0xD0,0x48,0x6f,0x6c,0x61,0x21,0x00,0x00}, //CRC 8 Hola!
{0x05,0xc2,0xCF,0xdb,0xD0,0x48,0x6f,0x6c,0x61,0x21,0x00,0x49} //CRC 8 Hola!
};
unsigned char g[][5]={"UTP", "OPTI", "COAX"};
unsigned char ng[][5]={" ", "BT", "WF", "ST"};
unsigned char gr[][5]={" ", "3CM2", "4CM1", "2CM6"};
unsigned char lg[][5]={"JPN", "ENG", "FRA", "ESP"};

unsigned char crc_8(unsigned char* t, unsigned char n){
  unsigned char p = 0x1b;
  unsigned char crc = 0x00;
  unsigned char doXor = 0;
  for (unsigned char i = 0; i < n; i++) {
    for (unsigned char j = 0x80; j > 0 ; j=j>>1) {
      doXor=0;
      if(crc&0x80) {
        doXor=1;
      }
      crc = crc<<1;
      if (t[i]&j) {
        crc = crc|1;
      }
      if(doXor==1){
        crc = crc^p;
      }
    }
  }
  return crc;
}


unsigned int crc_32(unsigned char *t, unsigned char n){
  unsigned int p = 0x04c11db7;
  unsigned int crc = 0;
  unsigned char doXor = 0;
  for (unsigned char i = 0; i < n; i++) {
    for (unsigned char j = 0x80; j > 0 ; j=j>>1) {
      doXor=0;
      if(crc&0x80000000) {
        doXor=1;
      }
      crc = crc<<1;
      if (t[i]&j) {
        crc = crc|1;
      }
      if(doXor==1){
        crc = crc^p;
      }
    }
  }
  return crc;
}

unsigned char bitsPrendidos(unsigned char *trama, unsigned char n){
  unsigned char  res = 0;
  for (unsigned char i = 0; i < n; i++) {
    for (unsigned char j = 128; j > 0 ; j=j>>1) {
      if(trama[i]&j){res++;}
    }
  }
  return res;
}

unsigned int checksum(unsigned char *trama, unsigned char n){
unsigned int sum = 0;
  for (unsigned char i = 0; i < n; i+=2) {
    sum += trama[i]<<8 + trama[i+1];
  }
  return sum;
}

void analizarTrama(unsigned char * t) {
  unsigned char n = 5+((t[4]>>3)&7)*3;
  for (size_t i = 5; i < n; i++) {
    printf("%c", t[i]);
  }
  printf("\n");
  switch ((t[1]>>2)&3) {
    //####################################CRC_8##################################################//
    case 0:
    case 1:
    case 2:
    n+=1;
    break;
    //####################################CRC_32#################################################//
    case 3:
    n+=4;
    break;
  }
  printf("Codigo de linea: ");
  if (t[0]&128)
    printf("Unipolar\n");
  if (t[0] & 64)
    printf("Bipolar\n");
  if (t[0] & 32)
    printf("Polar\n");
  if (t[0] & 16)
    printf("Not Return Zero\n");
  if (t[0] & 8)
    printf("Return Zero\n");
  if (t[0] & 4)
    printf("Diferencial\n");
  if (t[0] & 2)
    printf("No Diferencial\n");
  if (t[0] & 1)
    printf("Manchester\n");

  printf("Medio:");
  if (t[1]&128) {
    printf("%s\n", ng[(t[1]>>5)&3]);
  } else {
    printf("%s\n", g[(t[1]>>5)&3] );
  }

  printf("Control de flujo:");
  (t[1]&16)?printf("VD\n"):printf("P&E\n");
  printf("Control de error:");
  switch ((t[1]>>2)&3) {
    //####################################CRC_8##################################################//
    case 0:
    printf("CRC_8\n");
    printf("El CRC es  : %.2x\n",crc_8(t,n));
    break;
    //#####################################CheckSum##############################################//
    case 1:
    printf("CheckSum\n");
    printf("Resultante %x\n", checksum(t,n));
    printf("Comprobacion %x\n", ~(checksum(t,n)+~checksum(t,n)));
    break;
    //###################################Bit de paridad###########################################//
    case 2:
    printf("Bit de paridad ");
    if (t[1]&1) {
      printf("par\n");
      if (bitsPrendidos(t,n)%2==0) {
        printf("Trama incorrecta :(\n");
      }else{
        printf("Trama correcta :)\n");
      }
    }else{
      printf("impar\n");
      if (bitsPrendidos(t,n)%2==0) {
        printf("Trama correcta :)\n");
      }else{
        printf("Trama incorrecta :(\n");
      }
    }
    break;
    //####################################CRC_32#################################################//
    case 3:
    printf("CRC_32\n");
    printf("El CRC es  : %.8x \n",crc_32(t,n));
    break;
  }

  printf("Enrutamineto: ");
  (t[1]&2)?printf("Estatico\n"):printf("Dinamico\n");


  printf("Origen:\n");
  printf("Grupo %s : %d \n",gr[(t[2]>>6)&3] , (t[2]&63));
  printf("Destino:\n");
  printf("Grupo %s : %d \n",gr[(t[3]>>6)&3] , (t[3]&63));

  printf("Idioma: %s\n", lg[t[4]>>6&3] );


  printf("Tamaño: %d byte(s)\n",(((t[4]>>3)&7)*3));

  if (t[4]>>2&1) {
    printf("Fragmentado\n # Seq : %d \n",(t[4]&3));
  } else {
    printf("No Fragmentado\n");
  }

}


int main(int argc, char const *argv[]) {
  for (unsigned char i = 0; i <sizeof(tramas)/sizeof(tramas[0]); i++) {
    unsigned char * trama  = tramas[i];
    // printf("Size : %d \n",5+((trama[4]>>3)&7)*3);
    printf("Trama %d: ",i);
    // for (size_t j = 0; j < 5+((trama[4]>>3)&7)*3; j++) {
    //   printf("%.2x ", trama[j]);
    // }
    printf("\n");
    analizarTrama(trama);
    for (size_t i = 0; i < 50; i++) {
      printf("-");
    }
    printf("\n");
  }
}
