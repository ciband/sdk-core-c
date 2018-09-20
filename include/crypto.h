/**
 ****************************************************************************************
 *
 * @file crypto.h
 *
 * @XY4 project source code.
 *
 * @brief primary crypto routines for the XY4 firmware.
 *
 * Copyright (C) 2017 XY - The Findables Company
 *
 * This computer program includes Confidential, Proprietary Information of XY. 
 * All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef XYCrypto

/*
 * DEFINES
 ****************************************************************************************
 */

#define XYCrypto

/*
 * INCLUDES
 ****************************************************************************************
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "xyobject.h"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct Signer Signer;
typedef struct CryptoCreator CryptoCreator;

typedef struct{
  
  char* publicKey;
  char* privateKey;
} keyPairStruct;


/*
 * STRUCTURES
 ****************************************************************************************
 */

struct Signer{
  
  struct ByteArray* publicKey; // Cryptographic Public Key
  struct ByteArray* privateKey; // Cryptographic Private Key
  XYResult* (*getPublicKey)(Signer*);  // Returns public key
  XYResult* (*sign)(Signer*, struct ByteArray*); // Returns signed byte array
  
  /*
   * The method will take data and a cryptographic signature and a cryptographic public key
   * and determine if data was signed by the given public key correctly or if the signature
   * is malformed / invalid. Boolean return value.
   */
  
  int (*verify)(Signer*, struct ByteArray* data, struct ByteArray* sig, struct ByteArray* pubkey);
  ByteArray* (*encrypt)(struct Signer*, struct ByteArray*); // Encrypt the data to the key of this Signer object
  ByteArray* (*decrypt)(struct Signer*, struct ByteArray*); // Decrypt the data with the key of this Signer object.
};

struct CryptoCreator{
  
  char id[2];
  char* (*getId)(struct CryptoCreator*); // Fetch the above id object and return it.
  Signer* (*newInstance)(struct ByteArray* user_PrivateKey); // Generate a new Signer object which includes generating a new keypair.
};

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

char* cryptoGetId(CryptoCreator* object);
struct XYResult* getPublicKey(Signer* signer);
Signer* newInstance(ByteArray* user_PrivateKey);
CryptoCreator* newCryptoCreator(void);

#endif

// end of file crypto.h


