import CGTUI

public class AboutWindow: Window {
  public init(parent: Window? = nil) {
    super.init()
    self.nativePtr = gtui_create_aboutwindow()
    if let parent { self.setParent(parent) }
  }
  public required convenience init?(application: Application?) { self.init() }

  public func generalData(title: String, icon: Icon, developer: String, version: String)
    -> AboutWindow
  {
    gtui_aboutwindow_set_general_data(
      self.nativePtr,
      title.cString,
      icon.string.cString,
      developer.cString,
      version.cString
    )
    return self
  }

  public func website(url: String) -> AboutWindow {
    gtui_aboutwindow_set_website(self.nativePtr, url.cString)
    return self
  }

  public func support(url: String) -> AboutWindow {
    gtui_aboutwindow_set_support(self.nativePtr, url.cString)
    return self
  }

  public func issue(url: String) -> AboutWindow {
    gtui_aboutwindow_set_issue(self.nativePtr, url.cString)
    return self
  }

  public func addLink(title: String, url: String) -> AboutWindow {
    gtui_aboutwindow_add_link(self.nativePtr, title.cString, url.cString)
    return self
  }

  public func artists(_ artists: [String]) -> AboutWindow {
    gtui_aboutwindow_set_artists(self.nativePtr, artists.cArray)
    return self
  }

  public func designers(_ designers: [String]) -> AboutWindow {
    gtui_aboutwindow_set_designers(self.nativePtr, designers.cArray)
    return self
  }

  public func developers(_ developers: [String]) -> AboutWindow {
    gtui_aboutwindow_set_developers(self.nativePtr, developers.cArray)
    return self
  }

  public func documenters(_ documenters: [String]) -> AboutWindow {
    gtui_aboutwindow_set_documenters(self.nativePtr, documenters.cArray)
    return self
  }

  public func addCreditSection(title: String, people: [String]) -> AboutWindow {
    gtui_aboutwindow_add_credit_section(self.nativePtr, title.cString, people.cArray)
    return self
  }

  public func copyright(_ copyright: String) -> AboutWindow {
    gtui_aboutwindow_set_copyright(self.nativePtr, copyright.cString)
    return self
  }

  public func license(_ license: License) -> AboutWindow {
    gtui_aboutwindow_set_license(self.nativePtr, license.rawValue.cInt)
    return self
  }
}
