XCODE_PROJECT=serialization-cpp.xcodeproj
SCHEME=Serialization
TEST_SCHEME=SerializationTests

clean:
	git clean -ffdx

cmake-xcode-gen: clean
	cmake -G Xcode

cmake-clion-gen: clean
	cmake -G Ninja

build-mac: clean cmake-xcode-gen
	xcodebuild -project ${XCODE_PROJECT} -scheme ${SCHEME} build
	make cmake-clion-gen

test-mac: clean cmake-xcode-gen
	xcodebuild -project ${XCODE_PROJECT} -scheme ${TEST_SCHEME} test
	make cmake-clion-gen