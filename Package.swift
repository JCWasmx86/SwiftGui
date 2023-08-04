// swift-tools-version: 5.7
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
  name: "SwiftGui",
  products: [.library(name: "GTUI", targets: ["GTUI"])],
  dependencies: [
    // Dependencies declare other packages that this package depends on.
    // .package(url: /* package url */, from: "1.0.0"),
  ],
  targets: [
    // Targets are the basic building blocks of a package. A target can define a module or a test suite.
    // Targets can depend on other targets in this package, and on products in packages this package depends on.
    .systemLibrary(name: "CGTUI", pkgConfig: "libadwaita-1"),
    .target(name: "GTUI", dependencies: ["CGTUI"]),
    .executableTarget(name: "SwiftGui", dependencies: ["GTUI"]),
    .executableTarget(name: "Clicker", dependencies: ["GTUI"]),
    .testTarget(name: "SwiftGuiTests", dependencies: ["SwiftGui"]),
  ]
)
