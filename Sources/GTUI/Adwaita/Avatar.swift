import CGTUI

public class Avatar: NativeWidgetPeer {
  public init(size: Int, text: String? = nil, showInitials: Bool = true) {
    super.init()
    self.nativePtr = gtui_create_avatar(size.cInt, text?.cString, showInitials.cBool)
  }

  public func fallbackIcon(_ icon: Icon) -> Avatar {
    gtui_avatar_set_icon_name(self.nativePtr, icon.string.cString)
    return self
  }
}
