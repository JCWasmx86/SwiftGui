import GTUI

@main
public struct SwiftGui {

  public static func main() {
    let application = MyApplication()
    application.run()
  }
}

public class MyApplication: Application {
  public init() {
    super.init(name: "org.swift.Foo")
  }

  public override func onActivate() {
    let win = Window(app: self)
    let box1 = Box(horizontal: false).append(
      HeaderBar().packStart(Label("Headerlabel")).titleWidget(
        TitleBarWidget("Title", "Subtitle")
      )
    ).append(
      Label("Foo")
    ).append(
      MarkupLabel("<b>Foo</b>")
    ).append(
      Button("Click me").handler({
        print("Clicked")
      }))
    win.setChild(Scrolled().setChild(box1))
    win.show()
  }
}
