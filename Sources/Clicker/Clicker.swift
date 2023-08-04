import Foundation
import GTUI

@main
public struct Clicker {

  public static func main() {
    let application = ClickerApplication()
    application.run()
  }
}

public class ClickerApplication: Application {
  var n: Int
  public init() {
    self.n = 0
    super.init(name: "org.swift.Clicker")
  }

  public override func onActivate() {
    let win = Window(app: self)
    let lbl = Label("Clicked 0 time(s)")
    let box1 = Box(horizontal: false).append(
      HeaderBar().titleWidget(
        TitleBarWidget("Title", "Subtitle")
      )
    ).append(
      Scrolled().setChild(
        Box(horizontal: false).append(
          lbl.padding(10, .bottom)
        ).append(
          Button("Click me").handler({
            self.n += 1
            lbl.setText("Clicked \(self.n) time(s)")
          })
        ).padding(10)).vexpand(true))
    win.setChild(box1)
    win.maximize()
    win.show()
  }
}
