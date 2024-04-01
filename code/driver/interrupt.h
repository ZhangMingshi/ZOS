#ifndef _INTERRUPT_H
#define _INTERRUPT_H

typedef struct
{
    volatile unsigned int CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
    volatile unsigned int ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
    volatile unsigned int VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
    volatile unsigned int AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    volatile unsigned int SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
    volatile unsigned int CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
    volatile unsigned char SHP[12U];              /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    volatile unsigned int SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
    volatile unsigned int CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
    volatile unsigned int HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
    volatile unsigned int DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
    volatile unsigned int MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
    volatile unsigned int BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
    volatile unsigned int AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
    volatile unsigned int PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
    volatile unsigned int DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
    volatile unsigned int ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
    volatile unsigned int MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
    volatile unsigned int ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
             unsigned int RESERVED0[5U];
    volatile unsigned int CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

#define SCB_BASE_ADDR  0xE000ED00


#endif
