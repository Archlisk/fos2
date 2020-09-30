OUT = ../../Bin/Bootloader.bin

ASM = nasm
ASM_FLAGS += -fbin

SOURCE = Bootloader.asm

-include $(patsubst %.asm,%.d,$(SOURCE))

.PHONY: all
all: $(OUT)

$(OUT): $(SOURCE)
	$(ASM) $(ASM_FLAGS) $(SOURCE) -M -MT $(OUT) -MF $(patsubst %.asm,%.d,$(SOURCE))
	$(ASM) $(ASM_FLAGS) -o $(OUT) $(SOURCE)

.PHONY: clean
clean:
	rm $(OUT) $(patsubst %.asm,%.d,$(SOURCE))
