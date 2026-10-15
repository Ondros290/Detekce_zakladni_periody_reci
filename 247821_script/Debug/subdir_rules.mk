################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -g --include_path="C:/ti/ccsv8/tools/compiler/c6000_7.4.4/include" --include_path="D:/247821/Projekt/Debug" --include_path="C:/ti/bios_5_42_01_09/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_01_09/packages/ti/rtdx/include/c6000" --include_path="C:/ti/C6xCSL/include" --include_path="C:/ti/DSK6416/CCStudio/c6000/dsk6416/include" --define=c6416 --define=CHIP_6416 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1153783697:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1153783697-inproc

build-1153783697-inproc: ../hello.tcf
	@echo 'Building file: "$<"'
	@echo 'Invoking: TConf'
	"C:/ti/bios_5_42_01_09/xdctools/tconf" -b -Dconfig.importPath="C:/ti/bios_5_42_01_09/packages;" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hellocfg.cmd: build-1153783697 ../hello.tcf
hellocfg.s??: build-1153783697
hellocfg_c.c: build-1153783697
hellocfg.h: build-1153783697
hellocfg.h??: build-1153783697
hello.cdb: build-1153783697

%.obj: ./%.s?? $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -g --include_path="C:/ti/ccsv8/tools/compiler/c6000_7.4.4/include" --include_path="D:/247821/Projekt/Debug" --include_path="C:/ti/bios_5_42_01_09/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_01_09/packages/ti/rtdx/include/c6000" --include_path="C:/ti/C6xCSL/include" --include_path="C:/ti/DSK6416/CCStudio/c6000/dsk6416/include" --define=c6416 --define=CHIP_6416 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ./%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -g --include_path="C:/ti/ccsv8/tools/compiler/c6000_7.4.4/include" --include_path="D:/247821/Projekt/Debug" --include_path="C:/ti/bios_5_42_01_09/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_01_09/packages/ti/rtdx/include/c6000" --include_path="C:/ti/C6xCSL/include" --include_path="C:/ti/DSK6416/CCStudio/c6000/dsk6416/include" --define=c6416 --define=CHIP_6416 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


