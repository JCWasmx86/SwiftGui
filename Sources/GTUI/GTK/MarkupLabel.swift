import CGTUI
import Foundation

public class MarkupLabel: NativeWidgetPeer {
  public init(_ text: String) {
    super.init()
    self.nativePtr = gtui_create_markup_label(text.cString)
  }

  public func setText(_ text: String) {
    gtui_label_set_text(self.nativePtr, text.cString)
  }
}
