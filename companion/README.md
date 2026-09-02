# Nitmod Companion Service

The companion is the browser-side boundary for features that cannot run inside
a WASM side module. It currently exposes only a loopback health/capability
endpoint and deliberately has no administrative, persistence, screenshot or
anti-cheat operation yet.

The next bridge endpoints must use versioned JSON envelopes, authenticate the
game session, authorize each action server-side, and bind to loopback by
default. Do not expose this service on a public interface without TLS and an
authentication design.
