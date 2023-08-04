import CGTUI

public class TextView: NativeWidgetPeer {
  public override init() {
    super.init()
    self.nativePtr = gtui_create_textview()
  }

  public func contents() -> String {
    let contents = gtui_textview_contents(self.nativePtr)
    return String(cString: contents!)
  }
}
