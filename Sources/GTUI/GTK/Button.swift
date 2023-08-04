import CGTUI
import Foundation

public class Button: NativeWidgetPeer {
  var handlers: [() -> Void] = []

  public init(_ label: String) {
    super.init()
    self.nativePtr = gtui_create_button(label.cString)
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_button_init_signals(self.nativePtr, selfAddr)
  }
  public convenience init(_ label: String? = nil, icon: Icon) {
    self.init(label ?? "")
    gtui_button_set_child(
      self.nativePtr,
      ButtonContent(icon: icon, label: label).nativePtr
    )
  }

  public func handler(_ handler: @escaping () -> Void) -> Button {
    self.handlers.append(handler)
    return self
  }

  public func onClick() {
    for handler in self.handlers {
      handler()
    }
  }
}

@_cdecl("button_on_click_cb")
func button_on_click_cb(ptr: UnsafeMutableRawPointer, userData: UnsafeMutableRawPointer) {
  let button = Unmanaged<Button>.fromOpaque(userData).takeUnretainedValue()
  button.onClick()
}
