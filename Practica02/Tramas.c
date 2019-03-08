#include <stdio.h>
unsigned char t[]={0x48,0xc6,0xCF,0xBB,0x48,0x48,0x64,0x21};
unsigned char  g[][5]={"UTP", "OPTI", "COAX"};
unsigned char ng[][5]={" ", "BT", "WF", "ST"};
unsigned char gr[][5]={" ", "3CM2", "4CM1", "2CM6"};
unsigned char lg[][5]={"JPN", "ENG", "FRA", "ESP"};
int main(int argc, char const *argv[]) {
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
    case 0:
    printf(" \n");
    break;
    case 1:
    printf("CheckSum\n");
    break;
    case 2:
    printf("Bit de paridad\n");
    break;
    case 3:
    printf("CRC\n");
    break;
  }

  printf("Enrutamineto: ");
  (t[1]&2)?printf("Estatico\n"):printf("Dinamico\n");


  printf("Origen:\n");
  printf("Grupo %s : %d \n",gr[(t[2]>>6)&3] , (t[2]&63));
  printf("Destino:\n");
  printf("Grupo %s : %d \n",gr[(t[3]>>6)&3] , (t[3]&63));

  printf("Idioma: %s\n", lg[t[4]>>6&3] );


  printf("Tamaño: %d byte\n",(t[4]>>3&5));

  if (t[4]>>2&1) {
    printf("Fragmentado\n Byte # : %d ",(t[4]&3));
  } else {
    printf("No Fragmentado\n");
  }
  return 0;
}
