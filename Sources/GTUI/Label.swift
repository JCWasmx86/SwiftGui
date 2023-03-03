import CGTUI
import Foundation

public class Label: NativeWidgetPeer {
  public init(_ text: NSString) {
    super.init()
    self.nativePtr = gtui_create_label(UnsafePointer<CChar>(text.utf8String))
  }

  public func setText(_ text: NSString) {
    gtui_label_set_text(self.nativePtr, UnsafePointer<CChar>(text.utf8String))
  }
}
