#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

/*
 * COMMAND_NUMBER : 동시에 저장할 수 있는 최대 명령 개수
 * COMMAND_LENGTH : 각 명령(문자열)의 최대 길이
 */
#define COMMAND_NUMBER  10
#define COMMAND_LENGTH  40

volatile int fp_num;