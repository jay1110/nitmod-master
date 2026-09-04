# Original water events and native prediction

Original CG_EntityEvent cases 0x12..0x15 are water entry, exit, submersion
and resurfacing. Original cgs fields 69476/69480/69484/69488 register
water_in.wav, water_out.wav, water_un.wav and gasp.wav in cgame_client.c.
Native event numbers 18..21 instead name falling events, including unhandled
EV_FALL_FAR. This explains the reported Unknown event: 18 on original servers.

Received original events 18..21 now select the typed ET water handlers;
snapshot event/parameter/repeat bits stay unchanged. Submersion sound is
conditional on eventParm for original servers; resurfacing always plays the
exit sound, plus gasp when eventParm is nonzero. Reconstructed et260-layout
and stock server dispatch remain unchanged. Unsupported events still report
an error rather than silently dropping unknown gameplay behavior.

The post-Pmove transition explicitly uses native event dispatch for newly
predicted events. External server events, snapshot transitions and server
correction dispatch remain wire-aware. This separates locally generated ET
numbers from original-server numbers rather than using server identity alone
for both. Mixed server/predicted event-ring reconciliation still needs live
replay testing; this is not a full event enum or prediction protocol port.

Submersion retains the native 12-second breath HUD deadline. Original Nitmod's
extra skill-mask bit granting 15 seconds remains unported; no native skill bit
is guessed to represent it. No pak assets or native shared enums changed.

96 full-cgame profiles verify four water events, two parameter values, four
repeat-bit combinations and three origins (original wire, stock wire, native
prediction while connected to original Nitmod). They assert sound identity,
channel/entity, breath deadline and unchanged received event fields.
