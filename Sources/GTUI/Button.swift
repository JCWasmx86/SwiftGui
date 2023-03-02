import CGTUI
import Foundation

public class Button: NativeWidgetPeer {
  var handlers: [() -> ()] = []

  public init(_ label: NSString) {
  	super.init()
    self.nativePtr = gtui_create_button(UnsafePointer<CChar>(label.utf8String))
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_button_init_signals(self.nativePtr, selfAddr)
  }

  public func handler(_ handler: @escaping () -> ()) -> Button {
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
