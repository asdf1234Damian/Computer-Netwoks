#include <bitset>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<std::bitset<8>> ip;
  std::vector<std::bitset<8>> mask;
  unsigned char type = 0;
  unsigned char i = 0;

  for (char i = 0; i < 4; i++) {
    ip.push_back(std::bitset<8>(std::stoi(argv[i + 1])));
    mask.push_back(std::bitset<8>("00000000"));
  }
  // Class
  if (!ip[0][7]) { // Clase A
    std::cout << "A,";
    mask[0] = mask[0].flip();
    if (ip[1].none() && ip[2].none() && ip[3].none()) {
      std::cout << "-:-:-";
      type = 0;
    } else if (ip[1].all() && ip[2].all() && ip[3].all()) {
      std::cout << "-:-:-";
      type = 1;
    } else {
      type = 2;
      std::cout << ip[1].to_ulong() << ':'
                << ip[2].to_ulong() << ':'
                << ip[3].to_ulong();
    }
  } else if (!ip[0][6]) { // CLase B
    std::cout << "B,";
    mask[0] = mask[1] = mask[0].flip();
    if (ip[2].none() && ip[3].none()) {
      type = 0;
      std::cout << "-:-";
    } else if (ip[2].all() && ip[3].all()) {
      type = 1;
      std::cout << "-:-";
    } else {
      type = 2;
      std::cout << ip[2].to_ulong() << ':' << ip[3].to_ulong();
    }
  } else if (!ip[0][5]) { // Clase C
    std::cout << "C,";
    mask[0] = mask[1] = mask[2] = mask[0].flip();
    if (ip[3].none()) {
      type = 0;
      std::cout << "-";
    } else if (ip[3].all()) {
      type = 1;
      std::cout << "-";
    } else {
      type = 2;
      std::cout << ip[3].to_ulong();
    }
  } else {
    if (!ip[0][4]) { // Clase D
      std::cout << "D,";
      type= 0;
    } else { // Clase E
      std::cout << "E,";
      type= 1;
    }
    std::cout << std::bitset<4>(ip[0].to_string<char,std::string::traits_type,std::string::allocator_type>().substr(4,7)).to_ulong()
    <<':'<<ip[1].to_ulong()
    <<':'<<ip[2].to_ulong()
    <<':'<<ip[3].to_ulong()
    <<',';
    if (type) {
      std::cout << "Reservado" << ',';
    }else{
      std::cout << "Multicast" << ',';
    }
    std::cout << "-" << ',';
    std::cout << "-" << ',';
    std::cout << "-" << ',';
    std::cout << "-" ;
    return 0;
  }
  std::cout << ',';
  // Type
  switch (type) {
  case 0:
    std::cout << "Red";
    break;
  case 1:
    std::cout << "Broadcast";

    break;
  case 2:
    std::cout << "Host";
    break;
  }
  std::cout << ",";
  // Red
  std::cout << (ip[0] & mask[0]).to_ulong() << ':'
            << (ip[1] & mask[1]).to_ulong() << ':'
            << (ip[2] & mask[2]).to_ulong() << ':'
            << (ip[3] & mask[3]).to_ulong() << ',';
  // Broadcast
  std::cout << (ip[0] | mask[0].flip()).to_ulong() << ':'
            << (ip[1] | mask[1].flip()).to_ulong() << ':'
            << (ip[2] | mask[2].flip()).to_ulong() << ':'
            << (ip[3] | mask[3].flip()).to_ulong() << ',';
  for (i = 0; i < 4; i++) {
    mask[i].flip();
  }
  // Rango
  std::cout << (ip[0] & mask[0]).to_ulong() << ':'
            << (ip[1] & mask[1]).to_ulong() << ':'
            << (ip[2] & mask[2]).to_ulong() << ':'
            << (ip[3] & mask[3]).to_ulong()+1 << ',';
  std::cout << (ip[0] | mask[0].flip()).to_ulong() << ':'
            << (ip[1] | mask[1].flip()).to_ulong() << ':'
            << (ip[2] | mask[2].flip()).to_ulong() << ':'
            << ((ip[3] | mask[3].flip())).to_ulong()-1;
}
