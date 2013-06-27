
#include "CharlieCube.h"
#include "glcdfont.c"

CUBE *CUBE::activeObject = 0;
#if 0
u8 cube_buf[64]={
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};
#else
u8 cube_buf[CUBE_SIZE][CUBE_SIZE]={
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
};
uint8_t fb_buf[CUBE_SIZE][CUBE_SIZE];
#endif

u8 cube_level;
u8 cube_row;
u8 cube_column;

u8 cube_bit_map[8]={
  0x01, 0x02, 0x04, 0x08,
  0x10, 0x20, 0x40, 0x80
};

CUBE::CUBE()
{
  for(int i=0; i<64; i++){
    *((uint8_t *)cube_buf+i) = 0;
    *((uint8_t *)fb_buf+i) = 0;
  }

  cube_level = 0;
  cube_row = 0;
  cube_column = 0;
}

void CUBE :: init(void)
{
  u8 i;
  
  /** set mode and prescaler*/
	TCCR2A = 0x02;
	TCCR2B = 0x01;
	/** 16MHz count 2ms */
	TCNT2 = 0;
	OCR2A = 250;
	/** enable interrupt */
	TIMSK2 = 0x02;
  
  for(i=0; i<64; i++){
    *((uint8_t *)cube_buf+i) = 0xFF;
  }
  *((uint8_t *)cube_buf+29) = 0xAA;

  cube_level = 0;
  cube_row = 0;
  cube_column = 0;

}

void  CUBE :: write(uint8_t x, uint8_t y, uint8_t z, uint8_t val)
{
#if 0
	uint8_t cnt, tmp;
	cnt = 8*z+y;
	tmp = cube_bit_map[x];
	if(val){
		cube_buf[cnt] |= tmp;
	}else{
		cube_buf[cnt] &= ~tmp;
	}
#else
    uint8_t tmp;
	tmp = cube_bit_map[x];
	if(val){
		cube_buf[z][y] |= tmp;
	}else{
		cube_buf[z][y] &= ~tmp;
	}
#endif
}

void CUBE :: write(uint8_t layer, char c)
{
	int i, j;
	uint8_t tmp;
	uint8_t *pfont;
	pfont = font+(c*5);
	for(i=0; i<8; i++){
		if(i>0 && i<6){
			tmp = pgm_read_byte(pfont);
			pfont++;
		}else{
			tmp = 0;
		}
		for(j=0; j<8; j++){
			write(i, j, layer, tmp&(1<<j));
		}
	}
}

void CUBE :: write(uint8_t layer, uint8_t *pic)
{
	uint8_t cnt;
	int i;
	cnt = 8*layer;
	for(i=0; i<8; i++){
		cube_buf[layer][i] = pgm_read_byte(pic+i);
	}
}

/**
 * 	@brief turn on only one led one time, 512 times a period
 */
void CUBE :: scan(void)
{

  u8 p_val;
  u8 n_val;
  u8 cube_tmp;
#if 0
  /** calculate initial value */
  cube_tmp = cube_bit_map[cube_row];
  p_val = cube_buf[cube_cnt] & cube_tmp;
  n_val = cube_bit_map[cube_column];
#else
  /** calculate initial value */
  cube_tmp = cube_bit_map[cube_row];
  p_val = cube_buf[cube_level][cube_column] & cube_tmp;
  n_val = cube_bit_map[cube_column];
#endif
  /** reset all ports to hi-impedance */
  CUBE_OFF();

  switch(cube_level){
  case 0:
    CUBE_0_P = p_val;
    CUBE_0_N = ~n_val;
    CUBE_0_P_DIR = p_val;
    CUBE_0_N_DIR = n_val;
    break;
  case 1:
    CUBE_1_P = p_val;
    CUBE_1_N = ~n_val;
    CUBE_1_P_DIR = p_val;
    CUBE_1_N_DIR = n_val;
    break;	
  case 2:
    CUBE_2_P = p_val;
    CUBE_2_N = ~n_val;
    CUBE_2_P_DIR = p_val;
    CUBE_2_N_DIR = n_val;
    break;
  case 3:
    CUBE_3_P = p_val;
    CUBE_3_N = ~n_val;
    CUBE_3_P_DIR = p_val;
    CUBE_3_N_DIR = n_val;
    break;	
  case 4:
    CUBE_4_P = p_val;
    CUBE_4_N = ~n_val;
    CUBE_4_P_DIR = p_val;
    CUBE_4_N_DIR = n_val;
    break;
  case 5:
    CUBE_5_P = p_val;
    CUBE_5_N = ~n_val;
    CUBE_5_P_DIR = p_val;
    CUBE_5_N_DIR = n_val;
    break;	
  case 6:
    CUBE_6_P = p_val;
    CUBE_6_N = ~n_val;
    CUBE_6_P_DIR = p_val;
    CUBE_6_N_DIR = n_val;
    break;
  case 7:
    CUBE_7_P = p_val;
    CUBE_7_N = ~n_val;
    CUBE_7_P_DIR = p_val;
    CUBE_7_N_DIR = n_val;
    break;
  default:
    break; 		

  }

  /** next led */
  cube_row++;
  if(cube_row > 7){
    cube_row = 0;

    cube_column++;
    if(cube_column > 7){
      cube_column = 0;
      cube_level++;
      if(cube_level > 7){
        cube_level = 0;
      }
    }
    
  }

}

SIGNAL(TIMER2_COMPA_vect)
{
	CUBE *act = CUBE::activeObject;
	act->scan();
}

void CUBE :: argorder(int ix1, int ix2, int *ox1, int *ox2)
{
	if (ix1>ix2)
	{
		int tmp;
		tmp = ix1;
		ix1= ix2;
		ix2 = tmp;
	}
	*ox1 = ix1;
	*ox2 = ix2;
}
