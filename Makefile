CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTutorial: main.cpp
	g++ $(CFLAGS) -o VulkanTutorial main.cpp $(LDFLAGS)

.PHONY: test clean

drun:
	g++ $(CLFAGS) -g -o VulkanTutorial main.cpp $(LDFLAGS)
	./VulkanTutorial

clean:
	rm -f VulkanTutorial
