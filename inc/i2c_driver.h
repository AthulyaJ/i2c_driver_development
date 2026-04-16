#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H


/* 3 I2C are present in stm32f4 series  and i2c is hanging in APB Bus*/

#define I2C1BASEADDRS		APBBUSADDRS + I2C1OFFSET		
#define I2C2BASEADDRS		APBBUSADDRS + I2C2OFFSET
#define I2C3BASEADDRS		APBBUSADDRS + I2C3OFFSET

#define ENABLE		1
#define DISABLE 	0

/*peripheral register definition structure of I2C */ 

typedef struct
{
	__vo uint32_t CR1; 	//control register
	__vo uint32_t CR2;
	__vo uint32_t OAR1;	//used in slave mode for own address creation
	__vo uint32_t OAR1;	//used in slave mode for own address creation
	__vo uint32_t DR;	//data register holds data transferred or received
	__vo uint32_t SR1; 	//Status register
	__vo uint32_t SR2; 	//Status register 
	__vo uint32_t CCR; 	//Clock control register
	__vo uint32_t TRISE; 	//rising time of clock to reach from 30 % to 70% of voltage (used in initialization)
	__vo uint32_t FLTR;
}I2C_RegDef_t;


/* peripheral definition macro */

#define I2C1	((I2C_RegDef_t *)I2C1BASEADDRS)
#define I2C2	((I2C_RegDef_t *)I2C2BASEADDRS)
#define I2C3	((I2C_RegDef_t *)I2C3BASEADDRS)

/* clock enable macros for I2Cx peripherals */
#define I2C1_PCLK_ENABLE()	(RCC->APB1ENR |= (1<<21))	//21th bit for enabling the APB1 clock for I2C1
#define I2C2_PCLK_ENABLE()	(RCC->APB1ENR |= (1<<22))	//22nd bit for enabling the APB1 clock for I2C2
#define I2C3_PCLK_ENABLE()	(RCC->APB1ENR |= (1<<23))	//23rd bit for enabling the APB1 clock for I2C3

/* Bit position definition for I2C peripheral reg */
#define I2C_CR1_PE		0
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK		10
#define I2C_CR1_SWRST		15

#define I2C_CR2_FREQ		0
#define I2C_CR2_INTEREN		8
#define I2C_CR2_ITEEVTEN	9
#define I2C_CR2_ITBUFEN		10
#define I2C_CR2_DMAEN		11
#define I2C_CR2_LAST		12

#define I2C_SR1_SB		0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF		2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RxNE		6
#define I2C_SR1_TxE		7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF		10
#define I2C_SR1_OVR		11
#define I2C_SR1_PECERR		12
#define I2C_SR1_TIMEOUT		14
#define I2C_SR1_SMBALRT		15


#define I2C_SR2_PEC		15	//PEC[7:0]
#define I2C_SR2_DUALF		7
#define I2C_SR2_SMBHOST		6
#define I2C_SR2_SMBDEFAULT	5
#define I2C_SR2_GENCALL		4
#define I2C_SR2_TRA		3
#define I2C_SR2_BUSY		2
#define I2C_SR2_MSL		0

//i2c_ccr
#define I2C_CCR_F/S		15
#define I2C_CCR_DUTY		14
#define I2C_CCR_CCR		11	//[11:0]

/* I2C configuration and Handle structure */
typedef struct
{
	uint32_t I2CSCLSpeed;
	uint8_t	I2CDeviceAddress;
	uint8_t I2CACKControl;
	uint16_t I2CFMDutyCycle;
}I2C_Config_t;

/* Handle structure for i2c peripheral */
typedef struct
{
	I2C_RegDef_t	*pI2C;
	I2C_Config_t	I2CConfig;
}I2C_Handle_t;

/*i2c SCL speed */
#define I2C_SCL_SPEED_SM	100000	//standard mode 100kbit/sec
#define I2C_SCL_SPEED_FM2k	200000	//fast mode 400kbit/sec
#define I2C_SCL_SPEED_FM4k	400000	//fast mode 400kbit/sec

/*I2C ACK control - controlled by CR1 reg 10th bit*/
#define I2C_ACK_ENABLE		1
#define I2C_ACK_DISABLE 	0


//status flag definition[SR1]
#define I2C_FLAG_TxE	(1<<7)
#define I2C_FLAG_RxNE	(1<<6)
#define I2C_FLAG_SB	(1<<0)
#define I2C_FLAG_OVR	(1<<11)
#define I2C_FLAG_AF	(1<<10)
#define I2C_FLAG_ARLO	(1<<9)
#define I2C_FLAG_BERR	(1<<8)
#define I2C_FLAG_STOPF	(1<<4)
#define I2C_FLAG_ADD10	(1<<3)
#define I2C_FLAG_BTF	(1<<2)
#define I2C_FLAG_ADDR	(1<<1)
#define I2C_FLAG_TIMOUT	(1<<14)



//API's
uint32_t RCCGetPCLK1value(void);
void I2CPeripheralClockControl(I2C_RegDef_t *pI2C, uint8_t enordis);
void I2CInit(I2C_Handle_t *pI2CHandle);
void I2CGenerateStopCondition(I2C_RegDef_t *pI2C);
void I2CGenerateStartCondition(I2C_RegDef_t *pI2C);
uint8_t I2CGetFlagStatus(I2C_RegDef_t *pI2C,uint32_t FlagName);
void I2CClearAddressFlag(I2C_RegDef_t *pI2C);
void I2CExecuteAddressPhaseWrite(I2C_RegDef_t *pI2C,uint8_t SlaveAddress);
void I2CMasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t len,uint8_t SlaveAddrs);
	
	





#endif




	




	