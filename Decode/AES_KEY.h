#ifndef AES_KEY_H
#define AES_KEY_H

extern unsigned char Key[44][4];

void ExtendKey(void);

void UnLockData(unsigned char array_16[16]);
void UnLockBox(unsigned char *pBuffer);

#endif // AES_KEY_H
