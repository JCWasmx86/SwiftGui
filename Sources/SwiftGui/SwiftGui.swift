import GTUI

@main public struct SwiftGui {

  public static func main() {
    let application = MyApplication()
    application.run()
  }
}

public class MyApplication: Application {
  public init() { super.init(name: "org.swift.Foo") }

  func helloButton() -> Button { Button("Hello!").handler { print("Hello!") } }

  func aboutWindow(win: Window) -> AboutWindow {
    AboutWindow(parent: win).generalData(
      title: "SwiftGui",
      icon: .default(icon: .applicationXExecutable),
      developer: "JCWasmx86",
      version: "main"
    ).website(url: "https://github.com/JCWasmx86/SwiftGui").issue(
      url: "https://github.com/JCWasmx86/SwiftGui/issues"
    ).developers([
      "JCWasmx86 https://github.com/JCWasmx86", "david-swift https://github.com/david-swift",
    ]).copyright("© 2023 JCWasmx86, david-swift").license(.gpl3_0)
  }

  func toastOverlay(win: Window) -> ToastOverlay {
    var toastOverlay = ToastOverlay(Label(""))
    let carousel = Carousel().append(
      StatusPage().title("Hello").description("Page 1").hexpand().frame(minHeight: 300)
    ).append(StatusPage().title("World").description("Page 2").hexpand()).insert(
      Label("Inserted Page"),
      at: 0
    )
    let banner = Banner("Okay, so let's close the window.").buttonLabel("Close").buttonHandler {
      win.close()
    }
    toastOverlay = ToastOverlay(
      Box(horizontal: false).append(banner).append(
        StatusPage().title("Hello").description("World").icon(.default(icon: .softwareUpdateUrgent))
          .child(
            Box(horizontal: false, spacing: 5).append(MarkupLabel("<b>Foo</b> Bar")).append(
              Box(horizontal: false, spacing: 5).append(
                Box(spacing: 5).append(
                  Button("New Window").handler {
                    let otherWin = self.createWindow()
                    otherWin.show()
                  }.hexpand()
                ).append(
                  Button("Toast").handler {
                    let toast = Toast("Quit this <i>application!</i>").buttonLabel("Actions")
                      .buttonHandler {
                        let messageDialog = MessageDialog(
                          parent: win,
                          heading: "Hello, world!",
                          body: "Some body text"
                        ).response(id: "cancel", label: "Cancel", type: .closeResponse) {
                          print("Cancel")
                        }.response(id: "about", label: "About") {
                          self.aboutWindow(win: win).show()
                        }.response(
                          id: "quit",
                          label: "Quit",
                          appearance: .destructive,
                          type: .defaultResponse
                        ) {
                          print("Quit")
                          self.quit()
                        }.child(Avatar(size: 100).fallbackIcon(.default(icon: .dialogWarning)))
                        messageDialog.show()
                      }
                    toastOverlay.addToast(toast)
                  }.hexpand()
                ).append(
                  Button("Maximize").handler {
                    if win.isMaximized { win.unmaximize() } else { win.maximize() }
                  }.hexpand()
                ).append(
                  Button("Close").handler {
                    if banner.isRevealed { banner.hide() } else { banner.show() }
                  }.hexpand()
                )
              ).append(TextView()).append(TextDropDown().append("FOO").append("BAR")).frame(
                maxSize: 400
              )
            ).append(carousel.addIndicatorDots()).padding().vexpand()
          )
      )
    )
    return toastOverlay
  }

  func createWindow() -> Window {
    let win = Window(app: self)
    let tabView = TabView()
    let createTab = {
      var tab: UInt64 = 0
      _ = tabView.append(title: "Toast Overlay", self.toastOverlay(win: win)) { tab = $0 }
      return tab
    }
    let contentView = TabOverview().createTabHandler { createTab() }
    let box = Box(horizontal: false)
    _ = contentView.add(
      box.append(
        HeaderBar().packStart(helloButton()).titleWidget(TitleBarWidget("Title", "Subtitle"))
          .packEnd(Button(icon: .default(icon: .tabNew)).handler { _ = createTab() }).packEnd(
            TabButton(view: tabView).handler { contentView.showOverview() }
          )
      ).append(tabView.append(title: "Initial View", self.toastOverlay(win: win))).insert(
        TabBar(view: tabView),
        at: 1
      ),
      view: tabView
    )
    win.setChild(contentView)
    win.setDefaultSize(width: 700, height: 500)
    return win
  }

  public override func onActivate() {
    let win = createWindow()
    let preferencesWindow = PreferencesWindow(parent: win)
    let group = PreferencesGroup(name: "A Group", description: "Description")
    preferencesWindow.setDefaultSize(width: 500, height: 400)
    preferencesWindow.add(
      page: .init(name: "Hello", icon: .default(icon: .daytimeSunrise), description: "Hello world?")
        .add(
          group: group.add(
            ActionRow(title: "ActionRow", subtitle: "Description").addSuffix(
              helloButton().padding()
            )
          ).add(
            ComboRow(title: "ComboRow", subtitle: "Description").append("Hello").append("World")
          ).headerSuffix(
            Button("Add").handler {
              _ = group.add(
                ActionRow(
                  title: String(Int.random(in: 0...1000)),
                  subtitle: String(Int.random(in: 0...100000))
                )
              )
            }.padding()
          )
        ).add(
          group: .init(name: "Another Group", description: "Description").add(
            ExpanderRow(title: "ExpanderRow", subtitle: "Description").addRow(
              ActionRow(title: "Row 1", subtitle: "Description").addSuffix(helloButton().padding())
            ).addRow(ActionRow(title: "Row 2", subtitle: "Description"))
          )
        )
    )
    let entryRow = EntryRow(title: "Entry Row")
    let passwordEntryRow = PasswordEntryRow(title: "Password Entry Row")
    preferencesWindow.add(
      page: .init(name: "World", icon: .default(icon: .faceCool), description: "Cool!").add(
        group: .init(name: "Entries", description: "Description").add(
          entryRow.submitHandler {
            print(entryRow.contents())
            entryRow.setContents("")
          }
        ).add(passwordEntryRow).headerSuffix(
          Button("Print").handler {
            print("\(entryRow.contents()), \(passwordEntryRow.contents())")
          }.padding()
        )
      )
    )
    win.show()
    preferencesWindow.show()
    preferencesWindow.add(toast: .init("Toast!"))
  }
}
