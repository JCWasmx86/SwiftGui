public protocol InsertableContainer: Container {
  func insert(_ widget: NativeWidgetPeer, at index: Int) -> Self
}
