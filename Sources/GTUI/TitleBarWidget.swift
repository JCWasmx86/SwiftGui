import CGTUI
import Foundation

public class TitleBarWidget: NativeWidgetPeer {
  public init(_ title: NSString, _ subtitle: NSString) {
    super.init()
    self.nativePtr = gtui_create_title_bar_widget(
      UnsafePointer<CChar>(title.utf8String), UnsafePointer<CChar>(subtitle.utf8String))
  }
}
