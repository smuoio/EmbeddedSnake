void VIC_SetVectoredIRQ(void(*pIRQSub)(), unsigned int Priority,
                        unsigned int VicIntSource);

void Timer0IntrHandler (void);

void InitTimer0Interrupt();
