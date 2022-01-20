WORKSPACE=Serialization.xcworkspace
SCHEME=Serialization

build:
	xcodebuild -workspace ${WORKSPACE} -scheme ${SCHEME} build

test:
	xcodebuild -workspace ${WORKSPACE} -scheme ${SCHEME} test