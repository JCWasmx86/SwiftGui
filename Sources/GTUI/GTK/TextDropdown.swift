import CGTUI
import Foundation

public class TextDropDown: NativeWidgetPeer {
  private let stringListPtr: UInt64

  public override init() {
    self.stringListPtr = gtui_create_stringlist()
    super.init()
    self.nativePtr = gtui_create_text_dropdown(self.stringListPtr)
  }

  public func append(_ string: String) -> TextDropDown {
    gtui_stringlist_append(self.stringListPtr, string.cString)
    return self
  }

  public func selected() -> String {
    let str = gtui_stringlist_get_selected(self.nativePtr, self.stringListPtr)
    return String(cString: str!)
  }
}
