#ifndef TIMER_H
#define TIMER_H
#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1

void InitTimer23(void);
void InitTimer1(void);
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void);
#endif /* TIMER_H */