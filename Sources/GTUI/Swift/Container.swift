public protocol Container {
  func removeWidgets(_ widgets: [NativeWidgetPeer]) -> Self
  func removeAll() -> Self
  func getContent() -> [NativeWidgetPeer]
  func prepend(_ widget: NativeWidgetPeer) -> Self
  func append(_ widget: NativeWidgetPeer) -> Self
}
