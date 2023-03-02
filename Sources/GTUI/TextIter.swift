import CGTUI

public class TextIter: NativePeer {
  internal init(addr: UInt64) {
    super.init()
    self.nativePtr = addr
  }
}
