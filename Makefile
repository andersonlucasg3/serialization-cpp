XCODE_PROJECT=serialization-cpp.xcodeproj
VS_SOLUTION=serialization-cpp.sln
SCHEME=Serialization
TEST_SCHEME=SerializationTests

ifeq ($(OS),Windows_NT)
	RM_CMAKE_CACHE=del CMakeCache.txt
else
	RM_CMAKE_CACHE=rm CMakeCache.txt ||:
endif

cmake-clean:
	$(RM_CMAKE_CACHE)

cmake-xcode-gen:
	make cmake-clean
	cmake -G Xcode

cmake-clion-gen:
	make cmake-clean
	cmake -G Ninja

cmake-vs-gen:
	make cmake-clean
	cmake -G "Visual Studio 17 2022"

build-mac:
	make cmake-xcode-gen
	xcodebuild -project ${XCODE_PROJECT} -scheme ${SCHEME} build
	make cmake-clion-gen

test-mac:
	make cmake-xcode-gen
	xcodebuild -project ${XCODE_PROJECT} -scheme ${TEST_SCHEME} test
	make cmake-clion-gen

xcode-open:
	make cmake-xcode-gen
	open ./*.xcodeproj

vs-open:
	make cmake-vs-gen
	powershell -c "start ${VS_SOLUTION}"