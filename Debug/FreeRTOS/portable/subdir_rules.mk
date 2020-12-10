################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/port.obj: C:/Users/mjs47/OneDrive/School/The\ University\ of\ Wisconsin-Madison/3\ Junior\ Year/1\ Fall\ Semester/ECE\ 353/code-FreeRTOS/FreeRTOSv10.4.1/FreeRTOS/Source/portable/CCS/ARM_CM4F/port.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1010/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1010/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include" --include_path="C:/Users/mjs47/OneDrive/School/The University of Wisconsin-Madison/3 Junior Year/1 Fall Semester/ECE 353/code-FreeRTOS/FreeRTOSv10.4.1/FreeRTOS/Source/include" --include_path="C:/Users/mjs47/OneDrive/School/The University of Wisconsin-Madison/3 Junior Year/1 Fall Semester/ECE 353/code-FreeRTOS/FreeRTOSv10.4.1/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/mjs47/OneDrive/School/The University of Wisconsin-Madison/3 Junior Year/1 Fall Semester/ECE 353/code-FreeRTOS/Project" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/port.d_raw" --obj_directory="FreeRTOS/portable" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS/portable/portasm.obj: C:/Users/mjs47/OneDrive/School/The\ University\ of\ Wisconsin-Madison/3\ Junior\ Year/1\ Fall\ Semester/ECE\ 353/code-FreeRTOS/FreeRTOSv10.4.1/FreeRTOS/Source/portable/CCS/ARM_CM4F/portasm.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1010/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1010/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include" --include_path="C:/Users/mjs47/OneDrive/School/The University of Wisconsin-Madison/3 Junior Year/1 Fall Semester/ECE 353/code-FreeRTOS/FreeRTOSv10.4.1/FreeRTOS/Source/include" --include_path="C:/Users/mjs47/OneDrive/School/The University of Wisconsin-Madison/3 Junior Year/1 Fall Semester/ECE 353/code-FreeRTOS/FreeRTOSv10.4.1/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/mjs47/OneDrive/School/The University of Wisconsin-Madison/3 Junior Year/1 Fall Semester/ECE 353/code-FreeRTOS/Project" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/portasm.d_raw" --obj_directory="FreeRTOS/portable" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


