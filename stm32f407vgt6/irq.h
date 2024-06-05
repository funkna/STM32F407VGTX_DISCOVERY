// Redundancy Prevention --------------------------------------------------------------------------
#ifndef IRQ_H_
#define IRQ_H_

// Includes ---------------------------------------------------------------------------------------
// Defines ----------------------------------------------------------------------------------------
#define MAX_IRQ_NUMBER     (81)
#define MIN_IRQ_NUMBER     (0)
#define NUM_IRQ_NUMBERS    (MAX_IRQ_NUMBER - MIN_IRQ_NUMBER + 1)
#define MAX_IRQ_PRIORITY   (0x0F)
#define MIN_IRQ_PRIORITY   (0x00)

// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// IRQ Configuration Actions.
// -------------------------------------------------------------
typedef enum
{
   IRQ_ENABLE,
   IRQ_CLEAR
} IRQConfigActionEnum;

// -------------------------------------------------------------
// IRQ Priority Options.
// -------------------------------------------------------------
typedef enum
{
   IRQ_PRIORITY_0,
   IRQ_PRIORITY_1,
   IRQ_PRIORITY_2,
   IRQ_PRIORITY_3,
   IRQ_PRIORITY_4,
   IRQ_PRIORITY_5,
   IRQ_PRIORITY_6,
   IRQ_PRIORITY_7,
   IRQ_PRIORITY_8,
   IRQ_PRIORITY_9,
   IRQ_PRIORITY_10,
   IRQ_PRIORITY_11,
   IRQ_PRIORITY_12,
   IRQ_PRIORITY_13,
   IRQ_PRIORITY_14,
   IRQ_PRIORITY_15,
   IRQ_PRIORITY_MAX
} IRQPriorityEnum;

// -------------------------------------------------------------
// IRQ Vector Numbers.
// -------------------------------------------------------------
typedef enum
{
   IRQ_VECTOR_EXTI0 = 6,
   IRQ_VECTOR_EXTI1 = 7,
   IRQ_VECTOR_EXTI2 = 8,
   IRQ_VECTOR_EXTI3 = 9,
   IRQ_VECTOR_EXTI4 = 10,
   IRQ_VECTOR_I2C1_EV = 31,
   IRQ_VECTOR_I2C1_ER = 32,
   IRQ_VECTOR_I2C2_EV = 33,
   IRQ_VECTOR_I2C2_ER = 34,
   IRQ_VECTOR_I2C3_EV = 72,
   IRQ_VECTOR_I2C3_ER = 73,
   IRQ_VECTOR_SPI1 = 35,
   IRQ_VECTOR_SPI2 = 36,
   IRQ_VECTOR_SPI3 = 51,
   IRQ_VECTOR_USART1 = 37,
   IRQ_VECTOR_USART2 = 38,
   IRQ_VECTOR_USART3 = 39,
   IRQ_VECTOR_MAX = 82
} IRQVectorEnum;


// Functions --------------------------------------------------------------------------------------

#endif // IRQ_H_
