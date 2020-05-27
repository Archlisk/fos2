#pragma once

namespace Kernel {
namespace PIC {

void remap(u8 offset1, u8 offset2);

void mask_irq(u8 irq);
void unmask_irq(u8 irq);

void eoi(u8 irq);

void disable();

}
}
