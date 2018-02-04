//#define BLOCK_SIZE 16
//
//uint8_t key[BLOCK_SIZE] = {0xB7,0xEE,0x71,0x93,0xE3,0x95,0xF5,0xED,0x01,0x6E,0x48,0xFF,0x51,0xFA,0x11,0x80};
////uint8_t iv[BLOCK_SIZE] = {0x8F,0x6B,0xC2,0x45,0xA4,0x6A,0x1C,0x57,0x46,0xD8,0x95,0x9D,0x20,0x45,0x8F,0xAA};
//uint8_t iv[BLOCK_SIZE] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//
//void bufferSize(char* text, int &lengthi)
//{
//  int i = strlen(text);
//  int buf = round(i / BLOCK_SIZE) * BLOCK_SIZE;
//  lengthi = (buf < i) ? buf + BLOCK_SIZE : lengthi = buf;
//}
//
//void encrypt(char* plain_text, char* output, int lengthi)
//{
//  byte enciphered[lengthi];
//  AES aesEncryptor(key, iv, AES::AES_MODE_128, AES::CIPHER_ENCRYPT);
//  aesEncryptor.process((uint8_t*)plain_text, enciphered, lengthi);
//  int encrypted_size = sizeof(enciphered);
//  char encoded[encrypted_size];
//  base64_encode(encoded, (char*)enciphered, encrypted_size);
//  strcpy(output, encoded);
// strcpy(output, (char*)enciphered);
//}
//
//void decrypt(char* enciphered, char* output, int lengthi)
//{
//  lengthi = lengthi + 1; //re-adjust
//  int decodedLen = base64_dec_len(enciphered, lengthi);
//  char decoded[lengthi];
//  base64_decode(decoded, enciphered, lengthi);
//  bufferSize(enciphered, lengthi);
//  byte deciphered[lengthi];
//  AES aesDecryptor(key, iv, AES::AES_MODE_128, AES::CIPHER_DECRYPT);
//  aesDecryptor.process((uint8_t*)decoded, deciphered, lengthi);
//  strcpy(output, (char*)deciphered);
//}
//
//
// void mqtt_encrypt(char* output)
// {
//  //char plain_text[] = "test";
//  
//  // encrypt
//  int length = 0;
//  bufferSize(output, length);
//  char encrypted[length];
//  encrypt(output, encrypted, length);
// //    mqttClient.publish(will_msg,encrypted,true); 
//
//  strcpy(output, encrypted);
////
////  length = strlen(output);
////  char decrypted[length];
////  decrypt(output, decrypted, length);
////  mqttClient.publish(will_msg,decrypted,true);                  // publishes the device status to chennel 
////
//
// }

