extension Set where Element == Edge {
  public static var all: Self {
    vertical.union(horizontal)
  }

  public static var vertical: Self {
    top.union(bottom)
  }

  public static var horizontal: Self {
    leading.union(trailing)
  }

  public static var top: Self {
    [.top]
  }

  public static var bottom: Self {
    [.bottom]
  }

  public static var leading: Self {
    [.leading]
  }

  public static var trailing: Self {
    [.trailing]
  }

  public func add(_ edges: Self) -> Self {
    union(edges)
  }
}
