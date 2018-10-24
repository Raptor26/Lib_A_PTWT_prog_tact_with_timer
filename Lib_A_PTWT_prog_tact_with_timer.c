/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "Lib_A_PTWT_prog_tact_with_timer.h"
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/

/**
 * @brief	Функция выполняет инициализацию структуры для работы
 * 			программного такта
 * @param[in,out]	*pProgTact_s:	Указатель на структуру, в которой
 * 									содержится необходимая информация для
 * 									работы библиотеки
 * @param[in]	*pInitStruct:	Указатель на структуру, в которой содержится
 * 								необходимая информация для инициализации
 * 								структуры pProgTact_s
 * @return None
 */
ptwt_fnc_status_e
PTWT_Init_ProgTact(
	ptwt_prog_tact_s 				*pProgTact_s,
	ptwt_prog_tact_init_struct_s 	*pProgTactInit_s)
{
	pProgTact_s->initStatus_e = PTWT_ERROR;
	if ((pProgTactInit_s->pHardCnt != NULL)
			&& (pProgTactInit_s->progTactTime != 0u))
	{
		pProgTact_s->pHardCnt 		= pProgTactInit_s->pHardCnt;

		pProgTact_s->enable_flag 	= 1u;
		pProgTact_s->end_flag 		= 0u;
		pProgTact_s->overrun_cnt 	= 0u;
		pProgTact_s->progTactTime 	= pProgTactInit_s->progTactTime;
		pProgTact_s->restTime 		= 0u;
		pProgTact_s->initStatus_e	= PTWT_SUCCESS;
	}
	return (pProgTact_s->initStatus_e);
}

void
PTWT_ProgTact_StructInit(
	ptwt_prog_tact_init_struct_s *pInit_s)
{
	pInit_s->pHardCnt		= 0u;
	pInit_s->progTactTime	= 0u;
}

void
PTWT_ProgTactStartLoop(
	ptwt_prog_tact_s *pProgTact_s)
{
	/* Ожидание пока в прерывании не будет установлен флаг начала нового
	 * программного такта */
	while (pProgTact_s->enable_flag == 0u)
	{

	}

	/* Сброс флага */
	pProgTact_s->enable_flag = 0u;
}

/**
 * @brief	Функция находит остаток времени программного такта и устанавливает
 * 			флаг окончания такта. Также присутствует цикл, выход из которого
 * 			будет произведен после срабатывания прерывныя по переполнении
 * 			аппаратного таймера
 * @param[in,out]	*pProgTact_s:	Указатель на структуру, в которой
 * 									содержится необходимая информация для
 * 									работы библиотеки
 * @return None
 */
void
PTWT_ProgTactEndLoop(
	ptwt_prog_tact_s *pProgTact_s)
{
	/* Получение значения запаса времени программного такта */
	pProgTact_s->restTime =
		pProgTact_s->progTactTime - *pProgTact_s->pHardCnt;

	/* Установка флага окончания программного такта */
	pProgTact_s->end_flag++;
}

/**
 * @brief	Функция проверяет, уложилась ли программный такт в отведенное время
 * @param[in,out]	*pProgTact_s:	Указатель на структуру, в которой
 * 									содержится необходимая информация для
 * 									работы библиотеки
 * @return	Статус:
 * 			- PTWT_OK:	Программный такт уложился в отведенное время
 * 			- PTWT_OVERRUN_DETECT: Программный такт не уложился в отведенное время
 */
ptwt_status_e
PTWT_ProgTactOverrunDetect(
	ptwt_prog_tact_s *pProgTact_s)
{
	/* Если значение временной переменной не совпадает с текущим значением */
	if (pProgTact_s->overrun_cntTemp != pProgTact_s->overrun_cnt)
	{
		/* Присваивание текущего значения временной переменной */
		pProgTact_s->overrun_cntTemp =
			pProgTact_s->overrun_cnt;

		/* Возврат статуса переполнения */
		return (PTWT_OVERRUN_DETECT);
	}
	return (PTWT_OK);
}

/**
 * @brief	Функция устанавливает флаг начала нового программного такта и
 * 			проверяет, уложился ли такт в отведенное время
 * @warning	Функция должна быть помещена в обработчик прерывания, вызываемый по
 * 			переполнении аппаратного таймера
 * @param[in,out]	*pProgTact_s:	Указатель на структуру, в которой
 * 									содержится необходимая информация для
 * 									работы библиотеки
 * @return	None
 */
void
PTWT_ProgTactISR(
	ptwt_prog_tact_s *pProgTact_s)
{
	/* Разрешение нового программного такта */
	pProgTact_s->enable_flag++;

	/* Если не был завершен программный такт */
	if (pProgTact_s->end_flag == 0u)
	{
		/* Цикл программы не уложился в отведенное время */
		pProgTact_s->overrun_cnt++;
	}

	/* Сброс флага окончания программного такта */
	pProgTact_s->end_flag = 0u;
}
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
