#ifndef _KEY_H
#define _KEY_H

#define KEY0 PAin(0)
#define KEY1 PEin(4)
#define KEY2 PEin(3)
#define KEY3 PEin(2)

#define NO_KEY_PRESS 0
#define KEY0_PRESS 1
#define KEY1_PRESS 4
#define KEY2_PRESS 3
#define KEY3_PRESS 2


void KEY_Init(void);

u8 KEY_Scan(void);


#endif

