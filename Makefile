CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTutorial: main.cpp
	g++ $(CFLAGS) -o build/VulkanTutorial src/main.cpp $(LDFLAGS)

.PHONY: test clean

drun:
	g++ $(CLFAGS) -g -o build/VulkanTutorial src/main.cpp $(LDFLAGS)
	./build/VulkanTutorial

clean:
	rm -f build/VulkanTutorial
