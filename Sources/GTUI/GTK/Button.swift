import CGTUI
import Foundation

public class Button: NativeWidgetPeer {
  var handlers: [() -> Void] = []
  var content: ButtonContent?

  public init(_ label: String) {
    super.init()
    self.nativePtr = gtui_create_button(label.cString)
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_button_init_signals(self.nativePtr, selfAddr)
  }
  public convenience init(_ label: String? = nil, icon: Icon) {
    self.init(label ?? "")
    content = ButtonContent(icon: icon, label: label)
    if let content { gtui_button_set_child(self.nativePtr, content.nativePtr) }
  }

  public func handler(_ handler: @escaping () -> Void) -> Button {
    self.handlers.append(handler)
    return self
  }

  public func setLabel(_ text: String) { gtui_button_set_label(self.nativePtr, text.cString) }

  public func getContent() -> ButtonContent? { content }

  public func onClick() { for handler in self.handlers { handler() } }
}

@_cdecl("button_on_click_cb") func button_on_click_cb(
  ptr: UnsafeMutableRawPointer,
  userData: UnsafeMutableRawPointer
) {
  let button = Unmanaged<Button>.fromOpaque(userData).takeUnretainedValue()
  button.onClick()
}
