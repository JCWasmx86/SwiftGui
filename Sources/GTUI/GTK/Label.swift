import CGTUI
import Foundation

public class Label: NativeWidgetPeer {
  public init(_ text: String) {
    super.init()
    self.nativePtr = gtui_create_label(text.cString)
  }

  public func setText(_ text: String) {
    gtui_label_set_text(self.nativePtr, text.cString)
  }
}
