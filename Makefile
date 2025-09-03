CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTutorial: main.cpp
	g++ $(CFLAGS) -o build/VulkanTutorial src/main.cpp $(LDFLAGS)

lwlog:
	cmake -B build/ -S src/lwlog/ -DCMAKE_INSTALL_PREFIX=.

.PHONY: test clean

debug:
	cmake --build build/ --target install --config Debug
	g++ $(CLFAGS) -g -o build/VulkanTutorial src/main.cpp $(LDFLAGS)
	./build/VulkanTutorial

release:
	cmake --build build/ --target install --config Release
	g++ $(CLFAGS) -o build/VulkanTutorial src/main.cpp $(LDFLAGS)

clean:
	rm -f build/
