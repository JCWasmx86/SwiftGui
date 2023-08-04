format:
	swift-format -i --recursive Package.swift Sources/ Tests/
lint:
	swiftlint --progress Sources/ Tests/ Package.swift
clean:
	swift package clean

