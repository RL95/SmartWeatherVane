/*
 * DRV_PWM.c
 *
 *  Created on: Oct 12, 2022
 *      Author: R.Lin
 */

#include "DRV_PWM.h"

/**
  * @brief  Start all six PWM channels for MOSFETs
  * @note	Duty cycle for all channels is set to 0%
  */
void PWM_Start_All(){
	// set all PWM to 0% duty cycle
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	// start PWM channels
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	// start PWM complimentary channels
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);

	// start output compare on channel 4 for adc trigger
	//HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_4);
	//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	//HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_4);
}

// Stop all PWM channels
void PWM_Stop_ALL(){
	// stop PWM channels
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
	// stop PWM complimentary channels
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
	// set all PWM to 0% duty cycle
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
}

/**
  * @brief  Start PWM channel phase U high side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Start_UH(){
	TIM1->CCR1 = 0;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

/**
  * @brief  Start PWM channel phase V high side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Start_VH(){
	TIM1->CCR2 = 0;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

/**
  * @brief  Start PWM channel phase W high side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Start_WH(){
	TIM1->CCR3 = 0;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

/**
  * @brief  Start PWM channel phase U low side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Start_UL(){
	TIM1->CCR1 = 0;
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
}

/**
  * @brief  Start PWM channel phase V low side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Start_VL(){
	TIM1->CCR2 = 0;
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
}

/**
  * @brief  Start PWM channel phase W low side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Start_WL(){
	TIM1->CCR3 = 0;
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
}

/**
  * @brief  Stop PWM channel phase U high side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Stop_UH(){
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	TIM1->CCR1 = 0;
}

/**
  * @brief  Stop PWM channel phase V high side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Stop_VH(){
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	TIM1->CCR2 = 0;
}

/**
  * @brief  Stop PWM channel phase W high side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Stop_WH(){
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
	TIM1->CCR3 = 0;
}

/**
  * @brief  Stop PWM channel phase U low side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Stop_UL(){
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
	TIM1->CCR1 = 0;
}

/**
  * @brief  Stop PWM channel phase V low side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Stop_VL(){
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
	TIM1->CCR2 = 0;
}

/**
  * @brief  Stop PWM channel phase W low side MOSFET
  * @note	Duty cycle is set to 0% for phase high and low side alike
  */
void PWM_Stop_WL(){
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
	TIM1->CCR3 = 0;
}

/**
  * @brief  Set PWM channel phase U High side MOSFET to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_UH(bool state) {
	// set to high Z
	if (state) TIM1->CCER = TIM1->CCER & 0xFFFFFFFE; // set Capture/compare 1 output enable bit to 0
	// set to PWM control
	else TIM1->CCER = TIM1->CCER | 0x1; // set Capture/compare 1 output enable bit to 1
}

/**
  * @brief  Set PWM channel phase V High side MOSFET to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_VH(bool state) {
	// set to high Z
	if (state) TIM1->CCER = TIM1->CCER & 0xFFFFFFEF; // set Capture/compare 2 output enable bit to 0
	// set to PWM control
	else TIM1->CCER = TIM1->CCER | 0x10; // set Capture/compare 2 output enable bit to 1
}

/**
  * @brief  Set PWM channel phase W High side MOSFET to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_WH(bool state) {
	// set to high Z
	if (state) TIM1->CCER = TIM1->CCER & 0xFFFFFEFF; // set Capture/compare 3 output enable bit to 0
	// set to PWM control
	else TIM1->CCER = TIM1->CCER | 0x100; // set Capture/compare 3 output enable bit to 1
}

/**
  * @brief  Set PWM channel phase U low side MOSFET to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_UL(bool state) {
	// set to high Z
	if (state) TIM1->CCER = TIM1->CCER & 0xFFFFFFFB; // set Capture/compare 1 complementary output enable bit to 0
	// set to PWM control
	else TIM1->CCER = TIM1->CCER | 0x4; // set Capture/compare 1 complementary output enable bit to 1
}

/**
  * @brief  Set PWM channel phase V low side MOSFET to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_VL(bool state) {
	// set to high Z
	if (state) TIM1->CCER = TIM1->CCER & 0xFFFFFFBF; // set Capture/compare 2 complementary output enable bit to 0
	// set to PWM control
	else TIM1->CCER = TIM1->CCER | 0x40; // set Capture/compare 2 complementary output enable bit to 1
}

/**
  * @brief  Set PWM channel phase W low side MOSFET to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_WL(bool state) {
	// set to high Z
	if (state) TIM1->CCER = TIM1->CCER & 0xFFFFFBFF; // set Capture/compare 3 complementary output enable bit to 0
	// set to PWM control
	else TIM1->CCER = TIM1->CCER | 0x400; // set Capture/compare 3 complementary output enable bit to 1
}

/**
  * @brief  Set PWM channel phase U half-bridge MOSFETs to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_U(bool state){
	PWM_HZ_UH(state);
	PWM_HZ_UL(state);
}

/**
  * @brief  Set PWM channel phase V half-bridge MOSFETs to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_V(bool state){
	PWM_HZ_VH(state);
	PWM_HZ_VL(state);
}

/**
  * @brief  Set PWM channel phase W half-bridge MOSFETs to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_W(bool state){
	PWM_HZ_WH(state);
	PWM_HZ_WL(state);
}

/**
  * @brief  Set all PWM channel phase half-bridge MOSFETs to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ_ALL(bool state){
	PWM_HZ_U(state);
	PWM_HZ_V(state);
	PWM_HZ_W(state);
}

/*
* Compute CCR for Duty-cycle between 0% and 100%
* Internal clock frequency 170MHz and ARR register = 3400-1
* -> centre aligned PWM frequency (170MHz/ARR)/2 = 25kHz
* -> dead time of ~494ns (84t * (1/170MHz))
*/

/**
  * @brief  set PWM duty cycle to all channels
  * @param  float DC
  * 		Duty cycle set in percent
  * 		This parameter can be a value between 0.0 and 100.0
  */
void PWM_Set_DutyCycle_ALL(float DC){
	uint32_t CCR = 0;

	// make sure the input value is clamped between 0 and 100
	if((DC >= 0.0) | (DC <= 100.0)) CCR = htim1.Init.Period * DC * 0.01;

	// write to register
	TIM1->CCR1 = CCR;
	TIM1->CCR2 = CCR;
	TIM1->CCR3 = CCR;
}


/**
  * @brief  set PWM channel duty cycle
  * @param  int CH
  * 		which PWM channel to select
  *         This parameter can be one of the following values:
  *            @arg CH_1 : TIM Channel 1 selected
  *            @arg CH_2 : TIM Channel 2 selected
  *            @arg CH_3 : TIM Channel 3 selected
  *            @arg PHASE_U : TIM Channel 1 selected
  *            @arg PHASE_V : TIM Channel 2 selected
  *            @arg PHASE_W : TIM Channel 3 selected
  * @param  float DC
  * 		Duty cycle set in percent
  * 		This parameter can be a value between 0.0 and 100.0
  */
void PWM_Set_DutyCycle(int CH, float DC){
	uint32_t CCR = 0;

	// make sure the input value is clamped between 0 and 100
	if((DC >= 0.0) | (DC <= 100.0)) CCR = htim1.Init.Period * DC * 0.01;

	// write to register
    switch (CH){
	case CH_1: TIM1->CCR1 = CCR;
		break;
	case CH_2: TIM1->CCR2 = CCR;
		break;
	case CH_3: TIM1->CCR3 = CCR;
		break;
	default:
		TIM1->CCR1 = 0;
		TIM1->CCR2 = 0;
		TIM1->CCR3 = 0;
		break;
    }
}
