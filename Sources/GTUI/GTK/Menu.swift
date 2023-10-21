import CGTUI

public class Menu: NativePeer {
  private var labels: [String] = []

  public override init() {
    super.init()
    self.nativePtr = gtui_create_menu()
  }

  func initAction(
    _ label: String,
    app: Application? = nil,
    win: ApplicationWindow? = nil,
    id: String? = nil,
    handler: (() -> Void)? = nil
  ) -> String {
    let label = label.filter { $0.isLetter || $0.isNumber || $0 == "-" || $0 == "." }
    if let handler, let app {
      app.addKeyboardShortcut("", id: id ?? label, handler: handler)
      return "app.\(label)"
    }
    if let handler, let win {
      win.addKeyboardShortcut("", id: id ?? label, handler: handler)
      return "win.\(label)"
    }
    return id ?? ""
  }

  public func append(_ label: String, id: String) -> Menu {
    let fullID = initAction(label, id: id)
    gtui_menu_append(self.nativePtr, label.cString, fullID.cString)
    self.labels.append(label)
    return self
  }

  public func append(_ label: String, app: Application, handler: @escaping () -> Void) -> Menu {
    let id = initAction(label, app: app, handler: handler)
    return self.append(label, id: id)
  }

  public func append(_ label: String, window: ApplicationWindow, handler: @escaping () -> Void)
    -> Menu
  {
    let id = initAction(label, win: window, handler: handler)
    return self.append(label, id: id)
  }

  public func prepend(_ label: String, id: String) -> Menu {
    let fullID = initAction(label, id: id)
    gtui_menu_prepend(self.nativePtr, label, fullID)
    self.labels.insert(label, at: 0)
    return self
  }

  public func prepend(_ label: String, app: Application, handler: @escaping () -> Void) -> Menu {
    let id = initAction(label, app: app, handler: handler)
    return self.prepend(label, id: id)
  }

  public func prepend(_ label: String, window: ApplicationWindow, handler: @escaping () -> Void)
    -> Menu
  {
    let id = initAction(label, win: window, handler: handler)
    return self.prepend(label, id: id)
  }

  public func append(_ label: String, section: Menu) -> Menu {
    gtui_menu_append_section(self.nativePtr, section.nativePtr)
    self.labels.append(label)
    return self
  }

  public func prepend(_ label: String, section: Menu) -> Menu {
    gtui_menu_prepend_section(self.nativePtr, section.nativePtr)
    self.labels.insert(label, at: 0)
    return self
  }

  public func append(_ label: String, submenu: Menu) -> Menu {
    gtui_menu_append_submenu(self.nativePtr, label.cString, submenu.nativePtr)
    self.labels.append(label)
    return self
  }

  public func prepend(_ label: String, submenu: Menu) -> Menu {
    gtui_menu_prepend_submenu(self.nativePtr, label.cString, submenu.nativePtr)
    self.labels.insert(label, at: 0)
    return self
  }

  public func remove(at position: Int) {
    gtui_menu_remove(self.nativePtr, position.cInt)
    self.labels.remove(at: position)
  }

  public func remove(_ label: String) {
    if let index = self.labels.firstIndex(of: label) {
      gtui_menu_remove(self.nativePtr, index.cInt)
    }
    self.labels = self.labels.filter { $0 != label }
  }
}
