import CGTUI

public class MenuButton: NativeWidgetPeer {
  var content: ButtonContent?
  var menu: Menu = .init()

  public init(_ label: String) {
    super.init()
    self.nativePtr = gtui_create_menubutton()
    setLabel(label)
    gtui_menubutton_set_menu(self.nativePtr, menu.nativePtr)
  }
  public convenience init(_ label: String? = nil, icon: Icon) {
    self.init(label ?? "")
    content = ButtonContent(icon: icon, label: label)
    if let content { gtui_menubutton_set_child(self.nativePtr, content.nativePtr) }
  }

  public func setLabel(_ text: String) { gtui_menubutton_set_label(self.nativePtr, text.cString) }

  public func getContent() -> ButtonContent? { content }

  public func getMenu() -> Menu { menu }

  public func menu(edit: (Menu) -> Void) -> Self {
    edit(menu)
    return self
  }
}
