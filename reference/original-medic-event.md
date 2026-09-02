# Original Nitmod event 93: medic call

The remote server log on September 2 reports `Unknown event: 93` after
joining. This is a distinct fatal error from the earlier zone allocation
failure; the supplied fragment does not establish a causal relationship.

Evidence: sorted cgame_events.c CG_EntityEvent case 0x5d reads entity number,
looks up its client team, and calls trap_S_StartSound(NULL, number, 0, sound).
The two cgs sound fields at offsets 69648 and 69652 are initialized in
sorted cgame_client.c to sound/chat/axis/medic.wav and
sound/chat/allies/medic.wav. This exactly matches typed ET 2.60
EV_MEDIC_CALL, cgs.clientinfo[number].team and cgs.media.sndMedicCall[0/1].

CG_EntityEvent now maps the masked event 93 to the native dispatch value
only for original Nitmod serverinfo (gamename=nitmod, without the
reconstruction marker nitmod_csLayout=et260). It does not rewrite the
snapshot, change entity_event_t, or change qagame event numbers. Invalid
client numbers are rejected before accessing clientinfo for medic calls.
Original code lacks this explicit bounds check; it is intentional hardening.

The full-cgame fixture tests 48 combinations of three server identities,
four teams and four event-repeat bit patterns. It verifies exact sound,
entity and channel, spectator/free silence, and unchanged entityState_t.
Six additional out-of-range-number calls verify no sound is dispatched.

Only this evidenced event mapping is implemented here. Other original
event IDs, weapon IDs and snapshot semantics still require an audited
translation; fatal handling of unknown events remains enabled. Local tests
and a rebuilt side module do not establish original-server gameplay parity
or resolve the previously reported allocator failure.
