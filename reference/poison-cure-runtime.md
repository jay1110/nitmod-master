# Poison cure runtime

Original qagame `Pickup_Health` consumes `g_poison` bits 2 and 8. Bit 2
allows health sources to clear poison. Bit 8 prevents the poison attacker from
curing that same victim with their health pack; other medics can still cure.
Health cabinets have no provider and cure whenever bit 2 is enabled.

The typed port clears the overloaded poison eFlag together with attacker,
stack and tick state. Both dropped health packs and cabinet healing call the
same bounded helper. No pak asset or menu file is changed.
