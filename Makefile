XCODE_PROJECT=serialization-cpp.xcodeproj
SCHEME=Serialization
TEST_SCHEME=SerializationTests

cmake-clean:
	rm CMakeCache.txt ||:

cmake-xcode-gen: cmake-clean
	cmake -G Xcode

cmake-clion-gen: cmake-clean
	cmake -G Ninja

build-mac: cmake-xcode-gen
	xcodebuild -project ${XCODE_PROJECT} -scheme ${SCHEME} build
	make cmake-clion-gen

test-mac: cmake-xcode-gen
	xcodebuild -project ${XCODE_PROJECT} -scheme ${TEST_SCHEME} test
	make cmake-clion-gen