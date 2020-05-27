#pragma once

#include <Drivers/Terminal.h>
#include <Heap.h>

namespace Kernel {

class KernelData {
public:
	static Terminal tty;
	static Heap heap;
};

}
