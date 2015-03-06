PART=TM4C123GH6PM
ROOT=${TI_DIR}
include ${ROOT}/makedefs
VPATH=${ROOT}/examples/boards/ek-tm4c123gxl/drivers
VPATH+=${ROOT}/utils
IPATH=${ROOT}/examples/boards/ek-tm4c123gxl/
IPATH+=${ROOT}

all: ${COMPILER}
all: ${COMPILER}/main.axf

clean:
	@rm -rf ${COMPILER} ${wildcard *~}

${COMPILER}:
	@mkdir -p ${COMPILER}
all:
${COMPILER}/main.axf: ${COMPILER}/main.o
${COMPILER}/main.axf: ${COMPILER}/led.o
${COMPILER}/main.axf: ${COMPILER}/adc.o
${COMPILER}/main.axf: ${COMPILER}/master_commands.o
${COMPILER}/main.axf: ${COMPILER}/uartstdio.o
${COMPILER}/main.axf: ${COMPILER}/cmdline.o
${COMPILER}/main.axf: ${COMPILER}/utils.o
${COMPILER}/main.axf: ${COMPILER}/effector.o
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
	sudo lm4flash -v ${COMPILER}/main.bin
