# SwiftGui

Attempts to bind parts of Libadwaita and GTK4 to Swift in a manner that makes it easy to use:

## Goals
- Good, usable API
- Extensions to API
- Capable of writing GNOME Apps, following the GNOME HIG.

## Non-Goals
- 1-1 Mapping of e.g. type names
- Following the C API closely

## Problems
- Memory management is currently "Leak a few widgets", but don't attempt to leak data.
