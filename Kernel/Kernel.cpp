#include <Drivers/Terminal.h>
#include <Drivers/VGA.h>

#include <Memory.h>

void kernel_main(Terminal& tty) {
	tty.set_color(VGA::BGColor4B::Black | VGA::FGColor4B::BrightWhite);
	tty.write_str("Fuck you\n");
}

extern "C"
void kernel_enter() {
	Terminal terminal((u16*)0xB8000, 80, 25);
	
	terminal.set_color(VGA::FGColor4B::LightGreen | VGA::BGColor4B::Black);
	terminal.write_str("Kernel entered\n");
	
	kernel_main(terminal);
	
	terminal.set_color(VGA::FGColor4B::LightRed | VGA::BGColor4B::Black);
	terminal.write_str("Kernel exiting...");
}
