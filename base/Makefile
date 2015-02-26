PART=TM4C123GH6PM
ROOT=/home/copiga/Projects/ti
include ${ROOT}/makedefs
VPATH=/home/copiga/Projects/ti/examples/boards/ek-tm4c123gxl/drivers
VPATH+=${ROOT}/utils
IPATH=/home/copiga/Projects/ti/examples/boards/ek-tm4c123gxl/
IPATH+=${ROOT}

all: ${COMPILER}
all: ${COMPILER}/main.axf

clean:
	@rm -rf ${COMPILER} ${wildcard *~}

${COMPILER}:
	@mkdir -p ${COMPILER}

${COMPILER}/main.axf: ${COMPILER}/main.o
${COMPILER}/main.axf: ${COMPILER}/led.o
${COMPILER}/main.axf: ${COMPILER}/adc.o
${COMPILER}/main.axf: ${COMPILER}/uartstdio.o
#example build rule, replace the .c part of the c filename with .o
#${COMPILER}/main.axf: ${COMPILER}/mysourcefile.o
${COMPILER}/main.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/main.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/main.axf: main.ld
SCATTERgcc_main=main.ld
ENTRY_main=ResetISR
CFLAGSgcc=-DTARGET_IS_BLIZZARD_RB1 -DUART_BUFFERED


ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif

deploy:
	lm4flash ${COMPILER}/main.bin
