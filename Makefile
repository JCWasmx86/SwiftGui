format:
	clang-format -i Sources/CGTUI/shim.h  --style=file
	swift-format -i --recursive Package.swift Sources/ Tests/
lint:
	swiftlint --progress Sources/ Tests/ Package.swift
clean:
	swift package clean

