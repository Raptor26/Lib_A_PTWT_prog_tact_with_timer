/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


#ifndef LIB_A_PTWT_PROG_TACT_WITH_TIMER_H_
#define LIB_A_PTWT_PROG_TACT_WITH_TIMER_H_


/*#### |Begin| --> Секция - "Include" ########################################*/
/*==== |Begin| --> Секция - "C libraries" ====================================*/
#include "stdio.h"
#include "stdint.h"
/*==== |End  | <-- Секция - "C libraries" ====================================*/

/*==== |Begin| --> Секция - "MK peripheral libraries" ========================*/
/*==== |End  | <-- Секция - "MK peripheral libraries" ========================*/

/*==== |Begin| --> Секция - "Extern libraries" ===============================*/
/*==== |End  | <-- Секция - "Extern libraries" ===============================*/
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Определение констант" ###########################*/
/*#### |End  | <-- Секция - "Определение констант" ###########################*/


/*#### |Begin| --> Секция - "Определение типов" ##############################*/
typedef enum
{
	PTWT_ERROR = 0u,
	PTWT_SUCCESS,
} ptwt_fnc_status_e;

typedef enum
{
	PTWT_OK = 0u,
	PTWT_OVERRUN_DETECT,
} ptwt_status_e;

typedef struct
{
	/* Флаг начала нового программного цикла */
	size_t enable_flag;

	/* Счетчик количества событий, когда цикл не уложился в отведенный
	 * промежуток времени */
	size_t overrun_cnt;

	/* Переменная для хранения значения overrun_cnt */
	size_t overrun_cntTemp;

	/* Флаг окончания программного цикла.
	 * Данный флаг должен сбрасываться программно после завершения каждой
	 * итерации бесконечного цикла */
	size_t end_flag;

	/* Остаток времени после выполнения всего цикла (в тиках аппаратного счетчика) */
	uint16_t restTime;

	/**
	 * @brief	Указатель на регистр аппаратного счетчика, по переполнению
	 * 			которого происходит прерывание
	 */
	const uint16_t volatile *pHardCnt;

	/* Период времени программного такта в тиках аппаратного счетчика */
	uint16_t progTactTime;

	ptwt_fnc_status_e initStatus_e;
} ptwt_prog_tact_s;

typedef struct
{
	/**
	 * @brief	Указатель на регистр аппаратного счетчика, по переполнению
	 * 			которого происходит прерывание
	 */
	uint16_t *pHardCnt;

	/**
	 * @brief	Время программного такта в тиках аппаратного счетчика
	 */
	uint16_t progTactTime;
} ptwt_prog_tact_init_struct_s;
/*#### |End  | <-- Секция - "Определение типов" ##############################*/


/*#### |Begin| --> Секция - "Определение глобальных переменных" ##############*/
/*#### |End  | <-- Секция - "Определение глобальных переменных" ##############*/


/*#### |Begin| --> Секция - "Прототипы глобальных функций" ###################*/
extern ptwt_fnc_status_e
PTWT_Init_ProgTact(
	ptwt_prog_tact_s 				*pProgTact_s,
	ptwt_prog_tact_init_struct_s 	*pProgTactInit_s);

extern void
PTWT_ProgTact_StructInit(
	ptwt_prog_tact_init_struct_s    *pInit_s);

extern void
PTWT_ProgTactStartLoop(
	ptwt_prog_tact_s *pProgTact_s);

extern void
PTWT_ProgTactEndLoop(
	ptwt_prog_tact_s *pProgTact_s);

extern ptwt_status_e
PTWT_ProgTactOverrunDetect(
	ptwt_prog_tact_s *pProgTact_s);

extern void
PTWT_ProgTactISR(
	ptwt_prog_tact_s *pProgTact_s);
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif /* LIB_A_PTWT_PROG_TACT_WITH_TIMER_H_ */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
