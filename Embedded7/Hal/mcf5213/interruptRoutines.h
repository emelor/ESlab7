#ifndef INTERRUPTROUTINE_H
#define INTERRUPTROUTINE_H

void mcf5xxx_set_handler (int vector, void (*handler) (void));


asm void __declspec(register_abi) asm_set_ipl(int) ;



void mcf5xxx_irq_enable (void);
void mcf5xxx_irq_disable (void);

#endif