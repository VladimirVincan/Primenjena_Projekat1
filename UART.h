void initUART1(void);
void __attribute__((__interrupt__)) _U1RXInterrupt(void) ;
void WriteUART1(unsigned int data);
void RS232_putst(register const char *str);