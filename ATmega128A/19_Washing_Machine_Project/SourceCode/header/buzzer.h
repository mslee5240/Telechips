#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#include "isr.h"


// C, D, E, F, G, A, B(도, 레, 미, 파, 솔, 라, 시)
// 5옥타브 PWM 값
#define C5      1911    // 도
#define C5S     1817    // 도#
#define D5      1703    // 레
#define D5S     1607    // 레#
#define E5      1517    // 미
#define F5      1432    // 파
#define F5S     1352    // 파#
#define G5      1276    // 솔
#define G5S     1199    // 솔#
#define A5      1136    // 라
#define A5S     1073    // 라#
#define B5      1012    // 시

// 6옥타브 PWM 값
#define C6      956    // 도
#define C6S     909    // 도#
#define D6      851    // 레
#define D6S     804    // 레#
#define E6      758    // 미
#define F6      716    // 파
#define F6S     676    // 파#
#define G6      638    // 솔
#define G6S     602    // 솔#
#define A6      568    // 라
#define A6S     536    // 라#
#define B6      506    // 시

// 7옥타브 PWM 값
#define C7      478    // 도
#define C7S     450    // 도#
#define D7      425    // 레
#define D7S     401    // 레#
#define E7      378    // 미
#define F7      358    // 파
#define F7S     338    // 파#
#define G7      319    // 솔
#define G7S     301    // 솔#
#define A7      284    // 라
#define A7S     268    // 라#
#define B7      253    // 시

#define B_1_32		42
#define B_1_16		86
#define B_1_8		170
#define B_1_4		341
#define B_1_2		682
#define B_1			1364

void init_buzzer(void);
void music_player(int *tone, int *Beats);
void beep(void);
void mute(void);
void siren(int repeat);
void rrr(void);