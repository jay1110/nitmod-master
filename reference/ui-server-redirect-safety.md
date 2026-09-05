# Server redirect UI

Original UI_SetActiveMenu supports ET:// redirection and the redirect menu
action connects to com_errorMessage. Both paths remain available, but now
validate the destination and quote the connect argument. Hostnames, IPv4,
bracketed IPv6 and ports pass; whitespace, command separators, quotes and
path characters reject without executing anything. This is command-syntax
validation, not DNS/address reachability validation.

Prefix stripping uses memmove rather than overlapping Q_strncpyz. Invalid
automatic redirects use the existing popupError; invalid confirmations do
not clear the error or connect. This is a safety improvement over the original,
not a newly ported UI feature. No menu/PK3 files change.

UI fixture tests cover valid forms, mixed-case prefix, in-place conversion,
injection strings, null/empty input, output bounds and atomic rejection.
Live browser redirect verification remains pending.
