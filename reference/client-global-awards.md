# Original Nitmod global awards

The original cgame binary contains eleven usable global-award entries. Their
titles and descriptions were recovered directly from the immutable ELF string
data and are now represented as a bounded typed table.

`popaw <client> <award>` validates both fields before changing state. The
reconstructed popup uses the original right-side slide, blue 50-pixel panel,
three centered lines, configured notification hold/fade times, and one console
announcement. A normal `pop` and an award popup replace each other, matching
the original shared popup state instead of drawing overlapping notifications.

Invalid clients and award values never reach client-info or award-table array
accesses. Map lifecycle reset clears the popup.

No package or original binary was modified during extraction or integration.
