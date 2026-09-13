/*
 * name:		g_items.c
 *
 * desc:		Items are any object that a player can touch to gain some effect.
 *				Pickup will return the number of seconds until they should respawn.
 *				all items should pop when dropped in lava or slime.
 *				Respawnable items don't actually go away when picked up, they are
 *				just made invisible and untouchable.  This allows them to ride
 *				movers and respawn apropriately.
 *
*/

#include "g_local.h"
#include "nitmod_ammo_rewards.h"
#include "nitmod_weapon_ids.h"
#include "g_nitmod_restrictions.h"
#include "g_nitmod_weapon_definition.h"
#include "g_nitmod_etbot_lifecycle.h"
#include "g_nitmod_legacy_cvars.h"



#define RESPAWN_SP			-1
#define	RESPAWN_KEY			4
#define	RESPAWN_ARMOR		25
#define	RESPAWN_TEAM_WEAPON	30
#define	RESPAWN_HEALTH		35
#define	RESPAWN_AMMO		40
#define	RESPAWN_HOLDABLE	60
#define	RESPAWN_MEGAHEALTH	120
#define	RESPAWN_POWERUP		120
#define RESPAWN_PARTIAL		998		// for multi-stage ammo/health
#define RESPAWN_PARTIAL_DONE 999	// for multi-stage ammo/health


//======================================================================

/* MaxHP retains the original positive signed32 range. Keep the usual
 * add-and-clamp result defined even at INT_MAX (no signed overflow). */
static int G_NITMOD_AddPickupHealth(int health, int amount, int maximum) {
	long long next = (long long)health + amount;
	if(next > maximum) return maximum;
	return next < INT_MIN ? INT_MIN : (int)next;
}

int Pickup_Powerup( gentity_t *ent, gentity_t *other ) {
	gclient_t *client = other->client;
	int powerup = ent->item->giTag;
	int quantity = ent->item->quantity;

	/* Original tags are translated to the native powerup slots. */
	if( powerup == PW_OPS_DISGUISED ) {
		client->ps.eFlags &= ~EF_SPARE3;
		if( client->sess.sessionTeam != ent->item->giAmmoIndex ) {
			client->ps.powerups[PW_OPS_DISGUISED] = 1;
			client->ps.powerups[PW_OPS_CLASS_1] = quantity & 1;
			client->ps.powerups[PW_OPS_CLASS_2] = quantity & 2;
			client->ps.powerups[PW_OPS_CLASS_3] = quantity & 4;
			Q_strncpyz(client->disguiseNetname, client->pers.netname,
				sizeof(client->disguiseNetname));
			client->disguiseRank = client->sess.rank;
			ClientUserinfoChanged(other->s.clientNum);
		}
	} else if( powerup == PW_BREATHER ) {
		client->ps.eFlags &= ~EF_HEADSHOT;
	} else if( powerup >= 0 && powerup < MAX_POWERUPS ) {
		/* Quantities are milliseconds; no seconds rounding or stacking. */
		client->ps.powerups[powerup] = powerup == PW_NOFATIGUE || quantity == INT_MAX ?
			quantity : (int)((unsigned int)level.time + (unsigned int)quantity);
	}
	return RESPAWN_SP;
}

//----(SA) Wolf keys
//======================================================================
int Pickup_Key( gentity_t *ent, gentity_t *other )
{
	other->client->ps.stats[STAT_KEYS] |= ( 1 << ent->item->giTag );
	return RESPAWN_KEY;
}


#ifdef KITS

// START Mad Doc - TDF
// in single player, the player can pick up the 'kits' of dead allies. Kits contain ammo for the special weapons
// that bot was carrying
int Pickup_Kit( gentity_t *ent, gentity_t *other )
{

	switch (ent->item->giTag)
	{
		case KIT_ENGINEER:
				drop->item->giAmmoIndex = ps->ammoclip[BG_FindClipForWeapon(WP_LANDMINE)];
				drop->item->giClipIndex  = ps->ammoclip[BG_FindClipForWeapon(WP_DYNAMITE)];
				break;
			}
			case PC_FIELDOPS:
			{
				drop->item->giAmmoIndex = ps->ammoclip[BG_FindClipForWeapon(WP_AMMO)];
				drop->item->giClipIndex = ps->ammoclip[BG_FindClipForWeapon(WP_SMOKE_MARKER)];
				break;
			}
			case PC_COVERTOPS:
			{
				drop->item->giAmmoIndex = ps->ammoclip[BG_FindClipForWeapon(WP_SMOKE_BOMB)];
				// no second special for covert ops
				break;
			}

}
// END Mad Doc - TDF

#endif

/*
==============
Pickup_Clipboard
==============
*/
int Pickup_Clipboard( gentity_t *ent, gentity_t *other ) {

	if(ent->spawnflags & 4)
		return 0;	// leave in world

	return -1;
}


/*
==============
Pickup_Treasure
==============
*/
int Pickup_Treasure( gentity_t *ent, gentity_t *other )
{
	return -1;
}


/*
==============
UseHoldableItem
	server side handling of holdable item use
==============
*/
void UseHoldableItem( gentity_t *ent, int item ) {
	switch(item) {
		case HI_MEDKIT:
			ent->health = ent->client->ps.stats[STAT_MAX_HEALTH];
			break;

		case HI_WINE:		// 1921 Chateu Lafite - gives 25 pts health up to max health
			ent->health = G_NITMOD_AddPickupHealth(ent->health, 25,
				ent->client->ps.stats[STAT_MAX_HEALTH]);
			break;

		case HI_SKULL:		// skull of invulnerable - 30 sec invincible
			ent->client->ps.powerups[PW_INVULNERABLE] = level.time + 30000;
			break;

		case HI_WATER:		// protection from drowning - 30 sec underwater breathing time
			ent->client->ps.powerups[PW_BREATHER] = 30000;
			break;

		case HI_ELECTRIC:	// protection from electric attacks - absorbs 500 points of electric damage
			ent->client->ps.powerups[PW_ELECTRIC] = 500;
			break;
		
		case HI_FIRE:		// protection from fire attacks - absorbs 500 points of fire damage
			ent->client->ps.powerups[PW_FIRE] = 500;
			break;
		
		case HI_STAMINA:	// restores fatigue bar and sets "nofatigue" for a time period (currently forced to 60 sec)
			//----(SA)	NOTE:	currently only gives free nofatigue time, doesn't reset fatigue bar.
			//					(this is because I'd like the restore to be visually gradual (on the HUD item representing
			//					current status of your fatigue) rather than snapping back to 'full')
			ent->client->ps.powerups[PW_NOFATIGUE] = 60000;
			break;

		case HI_BOOK1:
		case HI_BOOK2:
		case HI_BOOK3:
			//G_AddEvent(	ent, EV_POPUPBOOK, (item - HI_BOOK1)+1 );
			break;
	}
}


//======================================================================

int Pickup_Holdable( gentity_t *ent, gentity_t *other ) {
	return RESPAWN_HOLDABLE;
}

// xkan, 10/26/2002
// extracted from Fill_Clip: add the specified ammount of ammo into the clip
// returns whether ammo was added to the clip
int AddToClip(
			  playerState_t *ps,// which player
			  int weapon,		// weapon to add ammo for
			  int ammomove,		// ammount to add. 0 means fill the clip if possible
			  int outOfReserve)	// is the amount to be added out of reserve
{
	int inclip, maxclip;
	int ammoweap = BG_FindAmmoForWeapon(weapon);

	/* Nitmod's dedicated thrown-knife pickup legitimately routes WP_KNIFE
	 * through Add_Ammo; base ET started this range at WP_LUGER. */
	if(weapon < WP_KNIFE || weapon >= WP_NUM_WEAPONS)
		return qfalse;

	inclip	= ps->ammoclip[BG_FindClipForWeapon(weapon)];
	maxclip = GetAmmoTableData(weapon)->maxclip;

	if (!ammomove)	// amount to add to the clip not specified
		ammomove = maxclip - inclip;	// max amount that can be moved into the clip
	else if (ammomove > maxclip - inclip)
		ammomove = maxclip - inclip;

	if (outOfReserve)
	{
		// cap move amount if it's more than you've got in reserve
		if(ammomove > ps->ammo[ammoweap])
			ammomove = ps->ammo[ammoweap];
	}

	if(ammomove) {
		if (outOfReserve)
			ps->ammo[ammoweap] -= ammomove;
		ps->ammoclip[BG_FindClipForWeapon(weapon)] += ammomove;
		return qtrue;
	}
	return qfalse;
}

//======================================================================

/*
==============
Fill_Clip
	push reserve ammo into available space in the clip
==============
*/
void Fill_Clip (playerState_t *ps, int weapon) {
	AddToClip(ps, weapon, 0, qtrue);
}

/*
==============
Add_Ammo
	Try to always add ammo here unless you have specific needs
	(like the AI "infinite ammo" where they get below 900 and force back up to 999)

	fillClip will push the ammo straight through into the clip and leave the rest in reserve
==============
*/
//----(SA)	modified
// xkan, 10/25/2002 - modified to return whether any ammo was added.
int Add_Ammo(gentity_t *ent, int weapon, int count, qboolean fillClip) {
	int ammoweap = BG_FindAmmoForWeapon(weapon);
	int originalCount;
	int maxammo = BG_MaxAmmoForWeapon( ammoweap, ent->client->sess.skill );
	if(ammoweap == WP_KNIFE) {
		int knifeClip = BG_FindClipForWeapon(WP_KNIFE);
		int before = ent->client->ps.ammoclip[knifeClip];
		maxammo = (ent->client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] & 32u) ? GetAmmoTableData(WP_KNIFE)->maxammo : 1;
		COM_BitSet(ent->client->ps.weapons, WP_KNIFE);
		ent->client->ps.ammoclip[knifeClip] += count;
		if(ent->client->ps.ammoclip[knifeClip] > maxammo) ent->client->ps.ammoclip[knifeClip] = maxammo;
		return ent->client->ps.ammoclip[knifeClip] > before;
	}
	if(ammoweap != WP_KNIFE) maxammo = NITMOD_AmmoRewardCapacity(ammoweap,
		ent->client->sess.nitmodSkillMasks,
		GetAmmoTableData(ammoweap)->maxammo, GetAmmoTableData(ammoweap)->maxclip);

	originalCount = ent->client->ps.ammo[ammoweap];

	if( ammoweap == WP_GRENADE_LAUNCHER ) {			// make sure if he picks up a grenade that he get's the "launcher" too
		COM_BitSet( ent->client->ps.weapons, WP_GRENADE_LAUNCHER );
		fillClip = qtrue;	// grenades always filter into the "clip"
	} else if( ammoweap == WP_GRENADE_PINEAPPLE ) {
		COM_BitSet( ent->client->ps.weapons, WP_GRENADE_PINEAPPLE );
		fillClip = qtrue;	// grenades always filter into the "clip"
	} else if (ammoweap == WP_DYNAMITE ) {
		COM_BitSet( ent->client->ps.weapons, WP_DYNAMITE);
		fillClip = qtrue;
	} else if (ammoweap == WP_SATCHEL_DET ) {
		COM_BitSet( ent->client->ps.weapons, WP_SATCHEL_DET );
		fillClip = qtrue;
	}

	/* Original 0x71bb0 transfers existing reserve for these four tools;
	 * it does not first credit the supplied count. */
	if(ammoweap == WP_GRENADE_LAUNCHER || ammoweap == WP_GRENADE_PINEAPPLE ||
	   ammoweap == WP_DYNAMITE || ammoweap == WP_SATCHEL_DET) {
		/* Ownership and forced clip fill were established above. */
	} else if( ammoweap == WP_PANZERFAUST || ammoweap == WP_FLAMETHROWER ) {
		ent->client->ps.ammoclip[ammoweap] += count;

		if( ent->client->ps.ammoclip[ammoweap] > maxammo ) {
			ent->client->ps.ammoclip[ammoweap] = maxammo;	// - ent->client->ps.ammoclip[BG_FindClipForWeapon(weapon)];
		}
	} else {
		ent->client->ps.ammo[ammoweap] += count;

		if( ent->client->ps.ammo[ammoweap] > maxammo ) {
			ent->client->ps.ammo[ammoweap] = maxammo;	// - ent->client->ps.ammoclip[BG_FindClipForWeapon(weapon)];
		}
	}

	/* Original 0x71ab5: fill from the newly credited reserve, after its cap. */
	if(fillClip) Fill_Clip(&ent->client->ps, weapon);

	if(count >= 999) { // 'really, give /all/'
		ent->client->ps.ammo[ammoweap] = count;
	}

	return (ent->client->ps.ammo[ammoweap] > originalCount);
}



/*
==============
Pickup_Ammo
==============
*/
int Pickup_Ammo (gentity_t *ent, gentity_t *other) {
	int density = ent->s.density ? ent->s.density : 1;
	/* Original Pickup_Ammo 0x720de: same drop lockout as weapon pickup. */
	if((int)((unsigned int)level.time - (unsigned int)other->client->dropWeaponTime) < 1000)
		return 0;
	if(ent->item->giTag == WP_AMMO)
		AddMagicAmmo(other, (int)((unsigned int)ent->count * (unsigned int)density));
	else
		Add_Ammo(other, ent->item->giTag, ent->count ? ent->count :
			(int)((unsigned int)ent->item->quantity * (unsigned int)density), qfalse);
	return ent->s.density == 2 ? RESPAWN_PARTIAL : RESPAWN_SP;
}

// xkan, 9/18/2002 - Extracted AddMagicAmmo from Pickup_Weapon()
/*
=================================================================
AddMagicAmmo - added the specified number of clips of magic ammo 
for any two-handed weapon

- returns whether any ammo was actually added
=================================================================
*/
qboolean AddMagicAmmo(gentity_t *receiver, int numOfClips) {
	return BG_AddMagicAmmoWar(&receiver->client->ps, receiver->client->sess.skill,
		receiver->client->sess.sessionTeam, numOfClips, receiver->client->sess.nitmodSkillMasks,
		(unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenaline", 0), G_NITMOD_ConfiguredWarMode());
}

//======================================================================

weapon_t G_GetPrimaryWeaponForClient( gclient_t *client )
{
	/* Original ELF 0x71ca0: inventory priority is independent of class/skill.
	 * Original weapon IDs: 5,29,33,6,30,24,23,22,31,10,3,8. */
	static const weapon_t priority[] = {
		WP_PANZERFAUST, WP_MOBILE_MG42, WP_MORTAR, WP_FLAMETHROWER,
		WP_K43, WP_GARAND, WP_CARBINE, WP_KAR98, WP_FG42,
		WP_STEN, WP_MP40, WP_THOMPSON
	};
	int i;
	if( !client || client->sess.sessionTeam == TEAM_SPECTATOR ) return WP_NONE;
	for( i = 0; i < (int)(sizeof(priority) / sizeof(priority[0])); ++i ) {
		if( COM_BitCheck(client->ps.weapons, priority[i]) ) return priority[i];
	}
	return WP_NONE;
}


void G_DropWeapon( gentity_t *ent, weapon_t weapon )
{
	vec3_t		angles, velocity, org, offset, mins, maxs;
	gclient_t	*client = ent->client;
	gentity_t	*ent2;
	gitem_t		*item;
	trace_t		tr;

	/* Original BG_FindItemForWeapon returns NULL immediately for WP_NONE. */
	if( weapon == WP_NONE ) return;
	item = BG_FindItemForWeapon( weapon );
	/* Original G_DropWeapon returns for WP_NONE/no item (ELF 0x72c75). */
	if(!item) return;
	VectorCopy( client->ps.viewangles, angles );
	/* Original knife drop has a five-degree yaw offset. */
	if(weapon == WP_KNIFE) angles[YAW] += 5.f;

	// clamp pitch
	if ( angles[PITCH] < -30 )
		angles[PITCH] = -30;
	else if ( angles[PITCH] > 30 )
		angles[PITCH] = 30;

	AngleVectors( angles, velocity, NULL, NULL );
	VectorScale( velocity, 64, offset );
	offset[2] += client->ps.viewheight / 2.f;
	VectorScale( velocity, 75, velocity );
	velocity[2] += 50 + random() * 35;

	VectorAdd( client->ps.origin, offset, org );

	VectorSet( mins, -ITEM_RADIUS, -ITEM_RADIUS, 0 );
	VectorSet( maxs, ITEM_RADIUS, ITEM_RADIUS, 2*ITEM_RADIUS );

	trap_Trace( &tr, client->ps.origin, mins, maxs, org, ent->s.number, MASK_SOLID );
	VectorCopy( tr.endpos, org );

	ent2 = LaunchItem( item, org, velocity, client->ps.clientNum );
	ent2->s.teamNum = client->sess.sessionTeam; /* Original ELF 0x72f2a..0x72f36. */
	COM_BitClear( client->ps.weapons, weapon );

	if( weapon == WP_KAR98 ) {
		COM_BitClear( client->ps.weapons, WP_GPG40 );
	} else if ( weapon == WP_CARBINE ) {
		COM_BitClear( client->ps.weapons, WP_M7 );
	} else if ( weapon == WP_FG42 ) {
		COM_BitClear( client->ps.weapons, WP_FG42SCOPE );
	} else if( weapon == WP_K43 ) {
		COM_BitClear( client->ps.weapons, WP_K43_SCOPE );
	} else if( weapon == WP_GARAND ) {
		COM_BitClear( client->ps.weapons, WP_GARAND_SCOPE );
	} else if( weapon == WP_MORTAR ) {
		COM_BitClear( client->ps.weapons, WP_MORTAR_SET );
	} else if( weapon == WP_MOBILE_MG42 ) {
		COM_BitClear( client->ps.weapons, WP_MOBILE_MG42_SET );
	}

	// Clear out empty weapon, change to next best weapon
	G_AddEvent( ent, EV_WEAPONSWITCHED, 0 );

	if( weapon == client->ps.weapon )
		client->ps.weapon = 0;

	if( weapon == WP_MORTAR ) {
		ent2->count = client->ps.ammo[BG_FindAmmoForWeapon(weapon)] + client->ps.ammoclip[BG_FindClipForWeapon(weapon)];
	} else {
		ent2->count = client->ps.ammoclip[BG_FindClipForWeapon(weapon)];
		ent2->nitmodDropAmmo = client->ps.ammo[BG_FindAmmoForWeapon(weapon)];
	}

	if( weapon == WP_KAR98 || weapon == WP_CARBINE ) {
		ent2->delay = client->ps.ammo[BG_FindAmmoForWeapon(weapAlts[weapon])];
	} else {
		ent2->delay = 0;
	}

//	ent2->item->quantity = client->ps.ammoclip[BG_FindClipForWeapon(weapon)]; // Gordon: um, modifying an item is not a good idea
	client->ps.ammoclip[BG_FindClipForWeapon(weapon)] = 0;
	/* Original 0x72f55..0x72f5f clears only the clip; reserve remains owned. */
	Bot_Event_RemoveWeapon(client->ps.clientNum, Bot_WeaponGameToBot(weapon));
}

// TAT 1/6/2003 - Bot picks up a new weapon
void BotPickupWeapon(int client, int weaponnum, qboolean alreadyHave);

qboolean G_CanPickupWeapon( weapon_t weapon, gentity_t* ent ) {
	int decision;
	unsigned int classMask;
	if(!ent || !ent->client || weapon < WP_NONE || weapon >= WP_NUM_WEAPONS) return qfalse;
	decision=G_NITMOD_PickupPrecheck(ent,weapon);
	if(decision>=0) return decision ? qtrue : qfalse;
	/* Original G_CanPickupWeapon uses the ordinary class allowlist when
	 * the private definition has no class bits, including missing scripts. */
	classMask = 0;
	G_NITMOD_PickupClassMask(weapon, &classMask);
	decision = G_NITMOD_CanPickupWeapon(ent, weapon, classMask);
	if(decision >= 0) return decision ? qtrue : qfalse;
	if( ent->client->sess.sessionTeam == TEAM_AXIS ) {
		if( weapon == WP_THOMPSON ) {
			weapon = WP_MP40;
		} else if( weapon == WP_CARBINE ) {
			weapon = WP_KAR98;
		} else if( weapon == WP_GARAND ) {
			weapon = WP_K43;
		}
		
	} else if( ent->client->sess.sessionTeam == TEAM_ALLIES ) {
		if( weapon == WP_MP40 ) {
			weapon = WP_THOMPSON;
		} else if( weapon == WP_KAR98 ) {
			weapon = WP_CARBINE;
		} else if( weapon == WP_K43 ) {
			weapon = WP_GARAND;
		}
	}

	if( ent->client->sess.skill[SK_HEAVY_WEAPONS] >= 4 && ( weapon == WP_THOMPSON || weapon == WP_MP40 ) ) {
		return qfalse;
	}

	return BG_WeaponIsPrimaryForClassAndTeam( ent->client->sess.playerType, ent->client->sess.sessionTeam, weapon );
}

int Pickup_Weapon( gentity_t *ent, gentity_t *other ) {
	int			quantity;
	int			reserveQuantity;
	int			options;
	qboolean	alreadyHave = qfalse;

	// JPW NERVE -- magic ammo for any two-handed weapon
	if( ent->item->giTag == WP_AMMO ) {
		AddMagicAmmo( other, ent->count );
		if (ent->parent) {
			Bot_Event_RecievedAmmo(other - g_entities, ent->parent);
			/* Original records the supplier before class/team reward checks. */
			if( ent->parent->client ) {
				other->client->pers.nitmodLastAmmoClient = ent->parent - g_entities;
			}
		}

		// if LT isn't giving ammo to self or another LT or the enemy, give him some props
		if( other->client->ps.stats[STAT_PLAYER_CLASS] != PC_FIELDOPS ) {
			if ( ent->parent && ent->parent->client && other->client->sess.sessionTeam == ent->parent->client->sess.sessionTeam ) {
				/* Original Pickup_Weapon checks g_misc bit 8 around the whole
				 * Field Ops reward block, including its cadence counter.
				 * The pack still supplies ammunition when rewards are disabled. */
				if( !(G_NITMOD_LegacyCvarInteger("g_misc", 0) & 8) ) {
					if (!(ent->parent->client->PCSpecialPickedUpCount % LT_SPECIAL_PICKUP_MOD)) {
						AddScore(ent->parent, WOLF_AMMO_UP);
						G_LogPrintf("Ammo_Pack: %d %d\n", (int)(ent->parent - g_entities), (int)(other - g_entities));	// OSP
					}
					ent->parent->client->PCSpecialPickedUpCount++;
					G_AddSkillPoints( ent->parent, SK_SIGNALS, 1.f );
					G_DebugAddSkillPoints( ent->parent, SK_SIGNALS, 1.f, "ammo pack picked up" );
				}

				/* Original 0x734d1: supply award counts even when g_misc8 blocks XP. */
				ent->parent->client->pers.nitmodAmmoSupplied = ent->parent->client->pers.nitmodAmmoSupplied == INT_MAX ? INT_MIN : ent->parent->client->pers.nitmodAmmoSupplied + 1;

				// extracted code originally here into AddMagicAmmo -xkan, 9/18/2002
				// add 1 clip of magic ammo for any two-handed weapon
			}
			return RESPAWN_SP;
		}
		/* Original returns after magic ammo for Field Ops too; do not treat
		 * the consumed WP_AMMO pack as a newly acquired primary weapon. */
		return RESPAWN_SP;
	}

	/* Original Pickup_Weapon handles thrown knives before g_weaponItems and
	 * firearm ownership. Each entity restores exactly one throwing knife; at
	 * eight stored knives it remains in the world. */
	if( ent->item->giTag == WP_KNIFE ) {
		int ammo = BG_FindClipForWeapon(WP_KNIFE);
		if( other->client->ps.ammoclip[ammo] > 7 ) return 0;
		Add_Ammo(other, WP_KNIFE, 1, qfalse);
		return -1;
	}

	quantity = ent->count;
	options = G_NITMOD_LegacyCvarInteger("g_weaponItems", 1);
	reserveQuantity = (options & 4) ? ent->nitmodDropAmmo : 0;

	// check if player already had the weapon
	alreadyHave = COM_BitCheck( other->client->ps.weapons, ent->item->giTag );

	// JPW NERVE  prevents drop/pickup weapon "quick reload" exploit
	if( alreadyHave ) {
		int ammoAdded = 0;
		/* Original Pickup_Weapon excludes wire IDs 23/24 (Carbine/Garand)
		 * from the clip-quantity grant when already owned. Separate dropped
		 * reserve and rifle-grenade quantities still follow their own paths. */
		if( quantity && ent->item->giTag != WP_CARBINE && ent->item->giTag != WP_GARAND ) {
			ammoAdded += Add_Ammo( other, ent->item->giTag, quantity, qfalse );
		}
		if( reserveQuantity ) {
			ammoAdded += Add_Ammo( other, ent->item->giTag, reserveQuantity, qfalse );
		}

		// Gordon: secondary weapon ammo
		if( ent->delay ) {
			ammoAdded += Add_Ammo( other, weapAlts[ ent->item->giTag ], ent->delay, qfalse );
		}
		/* Original bit 16 preserves an item which cannot contribute any ammo. */
		if( !ammoAdded && (options & 16) ) {
			return 0;
		}
		/* Bit 8 is the original ammo-only retention mode.  Pickup_Weapon
		 * returns zero so Touch_Item leaves the entity in the world; because
		 * that suppresses Touch_Item's normal feedback, emit it here first. */
		if( (options & 8) && ent->item->giTag != WP_BINOCULARS ) {
			if( quantity || ent->nitmodDropAmmo || ent->delay ) {
				int pickupEvent = EV_ITEM_PICKUP;
				if( ent->noise_index ) {
					G_AddEvent( other, EV_GENERAL_SOUND, ent->noise_index );
					pickupEvent = EV_ITEM_PICKUP_QUIET;
				}
				G_AddEvent( other, pickupEvent, ent->s.modelindex );
			}
			ent->count = 0;
			ent->nitmodDropAmmo = 0;
			ent->delay = 0;
			return 0;
		}
	} else {
		if( level.time - other->client->dropWeaponTime < 1000 ) {
			return 0;
		}

		if( other->client->ps.weapon == WP_MORTAR_SET || other->client->ps.weapon == WP_MOBILE_MG42_SET ) {
			return 0;
		}

		// See if we can pick it up
		if( G_CanPickupWeapon( ent->item->giTag, other ) ) {
			weapon_t primaryWeapon = G_GetPrimaryWeaponForClient( other->client );

			/* Original acquisition also works with an empty primary inventory. */
			{
				if( primaryWeapon && ent->item->giTag != WP_BINOCULARS ) {
					// drop our primary weapon
					G_DropWeapon( other, primaryWeapon );
				}

				if(other->client->ps.weapon == WP_GPG40 || other->client->ps.weapon == WP_M7)
					other->client->ps.weapon = WP_NONE;

				// now pickup the other one
				other->client->dropWeaponTime = level.time;

				// add the weapon
				COM_BitSet( other->client->ps.weapons, ent->item->giTag );

				// DHM - Fixup mauser/sniper issues
				if( ent->item->giTag == WP_FG42 ) {
					COM_BitSet( other->client->ps.weapons, WP_FG42SCOPE);
				} else if(ent->item->giTag == WP_GARAND) {
					COM_BitSet( other->client->ps.weapons, WP_GARAND_SCOPE);
				} else if( ent->item->giTag == WP_K43 ) {
					COM_BitSet( other->client->ps.weapons, WP_K43_SCOPE );
				} else if( ent->item->giTag == WP_MORTAR ) {
					COM_BitSet( other->client->ps.weapons, WP_MORTAR_SET );
				} else if( ent->item->giTag == WP_MOBILE_MG42 ) {
					COM_BitSet( other->client->ps.weapons, WP_MOBILE_MG42_SET );
				} else if( ent->item->giTag == WP_CARBINE ) {
					COM_BitSet( other->client->ps.weapons, WP_M7 );
				} else if( ent->item->giTag == WP_KAR98 ) {
					COM_BitSet( other->client->ps.weapons, WP_GPG40 );
				}

				other->client->ps.ammoclip[BG_FindClipForWeapon(ent->item->giTag)] = 0;
				other->client->ps.ammo[BG_FindAmmoForWeapon(ent->item->giTag)] = 0;

				if( ent->item->giTag == WP_MORTAR ) {
					other->client->ps.ammo[BG_FindClipForWeapon(ent->item->giTag)] = quantity;

					// Gordon: secondary weapon ammo
					if( ent->delay ) {
						Add_Ammo( other, weapAlts[ ent->item->giTag ], ent->delay, qfalse );
					}
				} else {
					other->client->ps.ammoclip[BG_FindClipForWeapon(ent->item->giTag)] = quantity;
					other->client->ps.ammo[BG_FindAmmoForWeapon(ent->item->giTag)] = reserveQuantity;

					// Gordon: secondary weapon ammo
					if( ent->delay ) {
						other->client->ps.ammo[ weapAlts[ ent->item->giTag ] ] = ent->delay;
					}
				}
			}
		} else {
			return 0;
		}
	}

	// TAT 1/6/2003 - If we are a bot, call the pickup function
	if( other->r.svFlags & SVF_BOT )
		BotPickupWeapon( other->s.number, ent->item->giTag, alreadyHave );
	Bot_Event_AddWeapon(other->client->ps.clientNum,
		Bot_WeaponGameToBot(ent->item->giTag));

	return -1;
}


//======================================================================

int Pickup_Health (gentity_t *ent, gentity_t *other) {
	int			max;
	int amount;
//	int			quantity = 0;
	/* Last supplier powers chat substitution; it is not a reward/assist
	 * eligibility flag. Original Pickup_Health updates it for medics too. */
	if( ent->parent && ent->parent->client ) {
		other->client->pers.nitmodLastHealthClient = ent->parent - g_entities;
	}

	// if medic isn't giving ammo to self or another medic or the enemy, give him some props
	if( other->client->ps.stats[STAT_PLAYER_CLASS] != PC_MEDIC ) {
		if( ent->parent && ent->parent->client && other->client->sess.sessionTeam == ent->parent->client->sess.sessionTeam ) {
			/* Original Pickup_Health gates the complete Medic reward block
			 * with g_misc bit 4. Healing and assist ownership stay active. */
			if( !(G_NITMOD_LegacyCvarInteger("g_misc", 0) & 4) ) {
				if (!(ent->parent->client->PCSpecialPickedUpCount % MEDIC_SPECIAL_PICKUP_MOD)) {
					AddScore(ent->parent, WOLF_HEALTH_UP);
					G_LogPrintf("Health_Pack: %d %d\n", (int)(ent->parent - g_entities), (int)(other - g_entities));	// OSP
				}
				ent->parent->client->PCSpecialPickedUpCount++;
				G_AddSkillPoints( ent->parent, SK_FIRST_AID, 1.f );
				G_DebugAddSkillPoints( ent->parent, SK_FIRST_AID, 1.f, "health pack picked up" );
			}
			/* Original 0x725e3: separate award counter, outside the XP gate. */
			ent->parent->client->sess.nitmodHealthSupplied = ent->parent->client->sess.nitmodHealthSupplied == INT_MAX ? INT_MIN : ent->parent->client->sess.nitmodHealthSupplied + 1;
		}
	}	
	
	max = BG_EffectiveMaxHealth(&other->client->ps);
	G_NITMOD_CurePoisonFromHealth(other, ent->parent, qfalse);

	/* Original 0x72622..72664: staged quantity precedes supplier reward. */
	amount = ent->s.density == 2 ? (int)((unsigned int)ent->item->quantity * 2u) :
		(ent->s.density == 0 || ent->s.density == 1) ? ent->item->quantity : 0;
	if(ent->parent && ent->parent->client &&
	   (ent->parent->client->sess.nitmodSkillMasks[SK_FIRST_AID] & 32u))
		amount = (int)((unsigned int)amount + 10u);
	other->health = G_NITMOD_AddPickupHealth(other->health, amount, max);
	other->client->ps.stats[STAT_HEALTH] = other->health;
	if(ent->s.density == 2) return RESPAWN_PARTIAL;
	if (ent->parent) {
		Bot_Event_Healed(other - g_entities, ent->parent);
	}

	return -1;
}

//======================================================================

/*
===============
RespawnItem
===============
*/
void RespawnItem( gentity_t *ent ) {
	// randomly select from teamed entities
	if (ent->team) {
		gentity_t	*master;
		int	count;
		int choice;

		if ( !ent->teammaster ) {
			G_Error( "RespawnItem: bad teammaster");
		}
		master = ent->teammaster;

		for (count = 0, ent = master; ent; ent = ent->teamchain, count++)
			;

		choice = rand() % count;

		for (count = 0, ent = master; count < choice; ent = ent->teamchain, count++)
			;
	}

	ent->r.contents = CONTENTS_TRIGGER;
	//ent->s.eFlags &= ~EF_NODRAW;
	ent->flags &= ~FL_NODRAW;
	ent->r.svFlags &= ~SVF_NOCLIENT;
	trap_LinkEntity (ent);

	// play the normal respawn sound only to nearby clients
	G_AddEvent( ent, EV_ITEM_RESPAWN, 0 );

	ent->nextthink = 0;
}


/*
==============
Touch_Item
	if other->client->pers.autoActivate == PICKUP_ACTIVATE	(0), he will pick up items only when using +activate
	if other->client->pers.autoActivate == PICKUP_TOUCH		(1), he will pickup items when touched
	if other->client->pers.autoActivate == PICKUP_FORCE		(2), he will pickup the next item when touched (and reset to PICKUP_ACTIVATE when done)
==============
*/
void Touch_Item_Auto( gentity_t *ent, gentity_t *other, trace_t *trace )
{
 	if( other->client->pers.autoActivate == PICKUP_ACTIVATE )
		return;

	if( !ent->active && ent->item->giType == IT_WEAPON ) {
		if( ent->item->giTag != WP_AMMO ) {
			if( !COM_BitCheck( other->client->ps.weapons, ent->item->giTag ) ) {
				return;	// force activate only
			}
		}
	}

	ent->active = qtrue;
	Touch_Item( ent, other, trace );

	if( other->client->pers.autoActivate == PICKUP_FORCE )		// autoactivate probably forced by the "Cmd_Activate_f()" function
		other->client->pers.autoActivate = PICKUP_ACTIVATE;		// so reset it.
}

/*
===============
Touch_Item
===============
*/
void Touch_Item( gentity_t *ent, gentity_t *other, trace_t *trace ) {
	int		respawn;
	int		makenoise = EV_ITEM_PICKUP;

	// only activated items can be picked up
	if( !ent->active ) {
		return;
	} else {
		// need to set active to false if player is maxed out
		ent->active = qfalse;
	}

	if( !other->client ) {
		return;
	}

	if( other->health <= 0 ) {
		return;		// dead people can't pickup
	}

	/* Original Touch_Item 0x73f2c/0x73fe8: playing dead forbids pickups;
	 * medics bit 1 or poison forbids a provider's own health pack. The owner
	 * comparison is s.clientNum, not a pointer or a class restriction. */
	if( other->client->ps.eFlags & EF_SPARE0 ) return;
	if( ent->item->giType == IT_HEALTH &&
		((G_NITMOD_ConfiguredMedicOptions() & 1u) ||
		 (other->client->ps.eFlags & NITMOD_EF_POISONED)) &&
		ent->parent && ent->parent->client &&
		ent->parent->s.clientNum == other->s.clientNum ) return;

	// the same pickup rules are used for client side and server side
	if ( !BG_CanItemBeGrabbedWar( &ent->s, &other->client->ps, other->client->sess.skill, other->client->sess.sessionTeam, other->client->sess.nitmodSkillMasks, (unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenaline", 0), G_NITMOD_ConfiguredWarMode() ) ) {
		return;
	}

	/* Original 0x73f8d: damaging flying items cannot be caught in air. */
	if(ent->damage && ent->s.pos.trType != TR_STATIONARY &&
	   ent->s.pos.trType != TR_GRAVITY_FLOAT && ent->s.pos.trType != TR_GRAVITY_PAUSED)
		return;

	if(g_gamestate.integer != GS_PLAYING) {
		// OSP - Don't let them pickup winning stuff in warmup
		if(ent->item->giType != IT_WEAPON &&
		   ent->item->giType != IT_AMMO &&
		   ent->item->giType != IT_HEALTH)
			return;
	}

//	G_LogPrintf( "Calling item pickup function for %s\n", ent->item->classname );

	// call the item-specific pickup function
	switch( ent->item->giType ) {
	case IT_WEAPON:
		respawn = Pickup_Weapon( ent, other );
		break;
	case IT_HEALTH:
		respawn = Pickup_Health(ent, other);
		break;
	case IT_AMMO:
		respawn = Pickup_Ammo(ent, other);
		break;
	case IT_TEAM:
		respawn = Pickup_Team(ent, other);
		break;
	default:
		return;
	}

//	G_LogPrintf( "Finished pickup function\n" );

	if ( !respawn ) {
		return;
	}

	G_LogPrintf( "Item: %i %s\n", other->s.number, ent->item->classname );

	// play sounds 
	if( ent->noise_index ) {
		// (SA) a sound was specified in the entity, so play that sound
		// (this G_AddEvent) and send the pickup as "EV_ITEM_PICKUP_QUIET"
		// so it doesn't make the default pickup sound when the pickup event is recieved
		makenoise = EV_ITEM_PICKUP_QUIET;
		G_AddEvent( other, EV_GENERAL_SOUND, ent->noise_index );
	}


	G_AddEvent( other, makenoise, ent->s.modelindex );

	// powerup pickups are global broadcasts
	if ( ent->item->giType == IT_TEAM ) {
		gentity_t* te = G_NITMOD_TempEvent( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
		te->s.eventParm = ent->s.modelindex;
		te->r.svFlags |= SVF_BROADCAST;
	}

//	G_LogPrintf( "Firing item targets\n" );

	// fire item targets
	G_UseTargets (ent, other);

	/* Original Touch_Item 0x740c3/0x74222: retain the next visible stage. */
	if(respawn == RESPAWN_PARTIAL && --ent->s.density) {
		ent->active = qtrue;
		trap_LinkEntity(ent);
		return;
	}

	// dropped items will not respawn
	if ( ent->flags & FL_DROPPED_ITEM ) {
		ent->freeAfterEvent = qtrue;
	}

	// picked up items still stay around, they just don't
	// draw anything.  This allows respawnable items
	// to be placed on movers.
	ent->r.svFlags |= SVF_NOCLIENT;
	ent->flags |= FL_NODRAW;
	ent->r.contents = 0;

	// ZOID
	// A negative respawn times means to never respawn this item (but don't 
	// delete it).  This is used by items that are respawned by third party 
	// events such as ctf flags
	if ( respawn <= 0 ) {
		ent->nextthink = 0;
		ent->think = 0;
	} else {
		ent->nextthink = level.time + respawn * 1000;
		ent->think = RespawnItem;
	}
	trap_LinkEntity( ent );
}


//======================================================================

/*
================
LaunchItem

Spawns an item and tosses it forward
================
*/
gentity_t *LaunchItem( gitem_t *item, vec3_t origin, vec3_t velocity, int ownerNum ) {
	gentity_t	*dropped;
	trace_t		tr;
	vec3_t		vec, temp;
	int			i;

	dropped = G_Spawn();

	dropped->s.eType = ET_ITEM;
	dropped->s.modelindex = item - bg_itemlist;	// store item number in modelindex
	dropped->s.otherEntityNum2 = 1;	// DHM - Nerve :: this is taking modelindex2's place for a dropped item

	dropped->classname = item->classname;
	G_NITMOD_SetTeamItemClassnameHash( dropped, item );
	dropped->item = item;
	VectorSet( dropped->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, 0 );			//----(SA)	so items sit on the ground
	VectorSet( dropped->r.maxs, ITEM_RADIUS, ITEM_RADIUS, 2*ITEM_RADIUS );	//----(SA)	so items sit on the ground
	dropped->r.contents = CONTENTS_TRIGGER|CONTENTS_ITEM;

	dropped->clipmask = CONTENTS_SOLID | CONTENTS_MISSILECLIP;		// NERVE - SMF - fix for items falling through grates

	dropped->touch = Touch_Item_Auto;

	trap_Trace( &tr, origin, dropped->r.mins, dropped->r.maxs, origin, ownerNum, MASK_SOLID );
	if ( tr.startsolid ) {
		VectorSubtract( g_entities[ownerNum].s.origin, origin, temp );
		VectorNormalize( temp );

		for ( i=16; i<=48; i+=16 ) {
			VectorScale( temp, i, vec );
			VectorAdd( origin, vec, origin );

			trap_Trace( &tr, origin, dropped->r.mins, dropped->r.maxs, origin, ownerNum, MASK_SOLID );
			if ( !tr.startsolid )
				break;
		}
	}

	G_SetOrigin( dropped, origin );
	dropped->s.pos.trType = TR_GRAVITY;
	dropped->s.pos.trTime = level.time;
	VectorCopy( velocity, dropped->s.pos.trDelta );

	// ydnar: set yaw to parent angles 
	temp[ PITCH ] = 0;
	temp[ YAW ] = g_entities[ ownerNum ].s.apos.trBase[ YAW ];
	temp[ ROLL ] = 0;
	G_SetAngle( dropped, temp );

	dropped->s.eFlags |= EF_BOUNCE_HALF;
	/* Original LaunchItem: drops slide and align independently of item type. */
	dropped->physicsBounce = 0.25f;
	dropped->nitmodItemSlide = qtrue;
	dropped->nitmodItemAlign = qtrue;

	if (item->giType == IT_TEAM) { // Special case for CTF flags
		gentity_t* flag = &g_entities[ g_entities[ownerNum].client->flagParent ];

		dropped->s.otherEntityNum =	g_entities[ownerNum].client->flagParent;	// store the entitynum of our original flag spawner
		dropped->s.density = 1;
		dropped->think = Team_DroppedFlagThink;
		dropped->nextthink = level.time + 30000;

		if( level.gameManager ) {
			G_Script_ScriptEvent( level.gameManager, "trigger", flag->item && flag->item->giTag == PW_REDFLAG ? "allied_object_dropped" : "axis_object_dropped" );
		}
		G_Script_ScriptEvent( flag, "trigger", "dropped" );
	} else { // auto-remove after 30 seconds
		dropped->think = G_FreeEntity;

		dropped->nextthink = level.time + 30000;
	}

	dropped->flags = FL_DROPPED_ITEM;

	/* Original supply stages depend on the first two model slots only. */
	if( item->giType == IT_HEALTH || item->giType == IT_AMMO ) {
		dropped->s.density = !item->world_model[0] ? -1 :
			(item->world_model[1] != NULL);
	}

	trap_LinkEntity (dropped);

	return dropped;
}

/*
================
Drop_Item

Spawns an item and tosses it forward
================
*/
gentity_t *Drop_Item( gentity_t *ent, gitem_t *item, float angle, qboolean novelocity) {
	vec3_t	velocity;
	vec3_t	angles;

	VectorCopy( ent->s.apos.trBase, angles );
	angles[YAW] += angle;
	angles[PITCH] = 0;	// always forward

	if (novelocity)
	{
		VectorClear (velocity);
	}
	else
	{
		AngleVectors( angles, velocity, NULL, NULL );
		VectorScale( velocity, 150, velocity );
		velocity[2] += 200 + crandom() * 50;
	}
	
	return LaunchItem( item, ent->s.pos.trBase, velocity, ent->s.number );
}


/*
================
Use_Item

Respawn the item
================
*/
void Use_Item( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	RespawnItem( ent );
}

//======================================================================

/*
================
FinishSpawningItem

Traces down to find where an item should rest, instead of letting them
free fall from their spawn points
================
*/
void FinishSpawningItem( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		dest;
	vec3_t		maxs;

	if ( ent->spawnflags & 1 )	// suspended
	{
		VectorSet( ent->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS );
		VectorSet( ent->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS );
		VectorCopy (ent->r.maxs, maxs);
	}
	else
	{
		// Rafael
		// had to modify this so that items would spawn in shelves
		VectorSet( ent->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, 0 );
		VectorSet( ent->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS );
		VectorCopy (ent->r.maxs, maxs);
		maxs[2] /= 2;
	}

	ent->r.contents = CONTENTS_TRIGGER|CONTENTS_ITEM;
	ent->touch = Touch_Item_Auto;
	ent->s.eType = ET_ITEM;
	ent->s.modelindex = ent->item - bg_itemlist;		// store item number in modelindex

	ent->s.otherEntityNum2 = 0;		// DHM - Nerve :: takes modelindex2's place in signaling a dropped item
//----(SA)	we don't use this (yet, anyway) so I'm taking it so you can specify a model for treasure items and clipboards
//	ent->s.modelindex2 = 0; // zero indicates this isn't a dropped item
	if(ent->model) {
		ent->s.modelindex2 = G_ModelIndex(ent->model);
	}

//----(SA)	added
	if(ent->item->giType == IT_TREASURE)
		ent->touch = Touch_Item;	// no auto-pickup, only activate
//----(SA)	end

	// using an item causes it to respawn
	ent->use = Use_Item;

//----(SA) moved this up so it happens for suspended items too (and made it a function)
	G_SetAngle (ent, ent->s.angles);

	if ( ent->spawnflags & 1 ) {	// suspended
		G_SetOrigin( ent, ent->s.origin );
	} else {
		
		VectorSet( dest, ent->s.origin[0], ent->s.origin[1], ent->s.origin[2] - 4096 );
		trap_Trace( &tr, ent->s.origin, ent->r.mins, maxs, dest, ent->s.number, MASK_SOLID );

		if ( tr.startsolid ) 
		{
			vec3_t temp;

			VectorCopy (ent->s.origin, temp);
			temp[2] -= ITEM_RADIUS; 

			VectorSet( dest, ent->s.origin[0], ent->s.origin[1], ent->s.origin[2] - 4096 );
			trap_Trace( &tr, temp, ent->r.mins, maxs, dest, ent->s.number, MASK_SOLID );
		}

#if 0
		// drop to floor
		VectorSet( dest, ent->s.origin[0], ent->s.origin[1], ent->s.origin[2] - 4096 );
		trap_Trace( &tr, ent->s.origin, ent->r.mins, maxs, dest, ent->s.number, MASK_SOLID );
#endif
		if ( tr.startsolid ) {
			G_Printf ("FinishSpawningItem: %s startsolid at %s\n", ent->classname, vtos(ent->s.origin));
			G_FreeEntity( ent );
			return;
		}

		// allow to ride movers
		ent->s.groundEntityNum = tr.entityNum;

		G_SetOrigin( ent, tr.endpos );
	}

	if (ent->spawnflags & 2)		// spin
	{
		ent->s.eFlags |= EF_SPINNING;
	}


	// team slaves and targeted items aren't present at start
	if ( ( ent->flags & FL_TEAMSLAVE ) || (ent->targetname && !ent->etxmapAutogeneratedName) ) {
		ent->flags |= FL_NODRAW;
		//ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		return;
	}

	// health/ammo can potentially be multi-stage (multiple use)
	if( ent->item->giType == IT_HEALTH || ent->item->giType == IT_AMMO ) {
		/* Original FinishSpawningItem uses the same two model checks as
		 * LaunchItem, rather than counting native ET's extra model slots. */
		ent->s.density = !ent->item->world_model[0] ? -1 :
			(ent->item->world_model[1] != NULL);
	}

	trap_LinkEntity (ent);
}


/*
============
G_SpawnItem

Sets the clipping size and plants the object on the floor.

Items can't be immediately dropped to floor, because they might
be on an entity that hasn't spawned yet.
============
*/
void G_SpawnItem (gentity_t *ent, gitem_t *item) {
	char	*noise;
	
	G_SpawnFloat( "random", "0", &ent->random );
	G_SpawnFloat( "wait", "0", &ent->wait );
	
	ent->item = item;
	// some movers spawn on the second frame, so delay item
	// spawns until the third frame so they can ride trains
	ent->nextthink = level.time + FRAMETIME * 2;
	ent->think = FinishSpawningItem;

	if(G_SpawnString("noise", 0, &noise))
		ent->noise_index = G_SoundIndex(noise);

	ent->nitmodItemSlide = qtrue;
	ent->nitmodItemAlign = qtrue;
	ent->physicsBounce = 0.50;		// items are bouncy

	if(ent->model) {
		ent->s.modelindex2 = G_ModelIndex(ent->model);
	}

	if ( item->giType == IT_TEAM ) {
		G_SpawnInt( "count", "1", &ent->s.density );
		G_SpawnInt( "speedscale", "100", &ent->splashDamage );
		if( !ent->splashDamage ) {
			ent->splashDamage = 100;
		}
	}
}


/*
================
G_BounceItem

================
*/
static void G_NITMOD_FlushItem( gentity_t *ent, trace_t *trace ) {
	int enabled = G_NITMOD_LegacyCvarInteger("g_flushItems", 1);

	if( !enabled || !ent->nitmodItemAlign || trace->plane.normal[2] <= 0.7f ||
		(trace->plane.normal[0] == 0.f && trace->plane.normal[1] == 0.f &&
		 trace->plane.normal[2] == 1.f) ) {
		trace->endpos[2] += 1.f;
		if( ent->nitmodItemAlign ) {
			ent->r.currentAngles[0] = 0.f;
			ent->r.currentAngles[2] = 0.f;
		}
	} else {
		vec3_t axis[3];
		vec3_t forward;
		vec3_t start;
		vec3_t end;
		trace_t backtrace;

		AngleVectors(ent->r.currentAngles, forward, NULL, NULL);
		VectorCopy(trace->plane.normal, axis[2]);
		ProjectPointOnPlane(axis[0], forward, axis[2]);
		if( VectorNormalize(axis[0]) == 0.f ) {
			AngleVectors(ent->r.currentAngles, NULL, NULL, axis[0]);
			ProjectPointOnPlane(axis[0], axis[0], axis[2]);
			VectorNormalize(axis[0]);
		}
		CrossProduct(axis[0], axis[2], axis[1]);
		VectorNegate(axis[1], axis[1]);
		AxisToAngles(axis, ent->r.currentAngles);

		VectorAdd(trace->endpos, axis[2], start);
		VectorMA(trace->endpos, -64.f, axis[2], end);
		trap_Trace(&backtrace, start, NULL, NULL, end, ent->s.number, CONTENTS_SOLID);
		if( !backtrace.startsolid )
			VectorMA(trace->endpos, -64.f * backtrace.fraction, axis[2], trace->endpos);
		VectorAdd(trace->endpos, axis[2], trace->endpos);
	}

	G_SetAngle(ent, ent->r.currentAngles);
	SnapVector(trace->endpos);
	G_SetOrigin(ent, trace->endpos);
	ent->s.groundEntityNum = trace->entityNum;
	if( trace->entityNum != ENTITYNUM_WORLD ) ent->s.pos.trType = TR_GRAVITY_PAUSED;
}

void G_BounceItem( gentity_t *ent, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	/* Preserve the original intermediate precision until integer truncation. */
	hitTime = (int)(level.previousTime + ( level.time - level.previousTime ) * (double)trace->fraction);
	BG_EvaluateTrajectoryDelta( &ent->s.pos, hitTime, velocity, qfalse, ent->s.effect2Time );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, ent->s.pos.trDelta );

	/* Original 0x751d8: steep surfaces slide before bounce damping. */
	if(trace->plane.normal[2] < 0.7 &&
	   VectorLength(ent->s.pos.trDelta) >= 16.f && ent->nitmodItemSlide) {
		PM_ClipVelocity(ent->s.pos.trDelta, trace->plane.normal, ent->s.pos.trDelta, 1.001f);
		goto continueMoving;
	}

	// cut the velocity to keep from bouncing forever
	VectorScale( ent->s.pos.trDelta, ent->physicsBounce, ent->s.pos.trDelta );

	if(ent->item && ent->item->giTag == WP_KNIFE)
		G_AddEvent(ent, EV_GRENADE_BOUNCE, BG_FootstepForSurface(trace->surfaceFlags));
	else if(ent->item && (ent->item->giType == IT_WEAPON || ent->item->giType == IT_AMMO) &&
	        NITMOD_OriginalWeaponId(ent->item->giTag) > 0)
		ent->s.weapon = ent->item->giTag;

	/* Original 0x75270: a knife sticks tip-first into soft surfaces. Keep
	 * that impact angle instead of flattening the item onto the floor. */
	if(ent->damage && ent->s.weapon == WP_KNIFE) {
		ent->nitmodItemAlign = qtrue;
		VectorNormalize(velocity);
		if(DotProduct(velocity, trace->plane.normal) <= -.75f &&
		   (trace->surfaceFlags & (SURF_WOOD|SURF_GRASS|SURF_GRAVEL|SURF_SNOW))) {
			vectoangles(velocity, ent->r.currentAngles);
			ent->nitmodItemAlign = qfalse;
			G_NITMOD_FlushItem(ent, trace);
			return;
		}
	}
	if(trace->plane.normal[2] > 0 && VectorLength(ent->s.pos.trDelta) < 40.f) {
		G_NITMOD_FlushItem(ent, trace);
		return;
	}
	if(ent->s.apos.trType != TR_STATIONARY) {
		VectorScale(ent->s.apos.trDelta, ent->physicsBounce, ent->s.apos.trDelta);
		ent->s.apos.trTime = level.time;
	}
continueMoving:
	VectorCopy(ent->r.currentOrigin, ent->s.pos.trBase);
	ent->s.pos.trTime = level.time;
	VectorAdd(ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
}

/*
=================
G_RunItemProp
=================
*/

void G_RunItemProp (gentity_t *ent, vec3_t origin)
{
	gentity_t	*traceEnt;
	trace_t		trace;
	gentity_t	*owner;
	vec3_t		start;
	vec3_t		end;

	owner = &g_entities[ent->r.ownerNum];

	VectorCopy (ent->r.currentOrigin, start);
	start[2] += 1;

	VectorCopy (origin, end);
	end[2] += 1;

	trap_Trace( &trace, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, end, 
				ent->r.ownerNum, MASK_SHOT );
			
	traceEnt = &g_entities[ trace.entityNum ];

	if (traceEnt && traceEnt->takedamage && traceEnt != ent)
		ent->enemy = traceEnt;

	if (owner->client && trace.startsolid && traceEnt != owner && traceEnt != ent/* && !traceEnt->active*/)
	{
				
		ent->takedamage = qfalse;
		ent->die (ent, ent, NULL, 10, 0);
		Prop_Break_Sound (ent);
				
		return;
	}
	else if ( trace.surfaceFlags & SURF_NOIMPACT) 
	{
		ent->takedamage = qfalse;
				
		Props_Chair_Skyboxtouch (ent);
								
		return;
	}
}

/* Original 0x755d0: supplied packs refill a finite cabinet before bouncing. */
static qboolean G_NITMOD_CheckForCabinetResupply(gentity_t *item, gentity_t *cabinet) {
	int i, amount;
	if(!cabinet || !item->item || !item->parent || !item->parent->client)
		return qfalse;
	if(item->item->giType == IT_HEALTH) {
		if(cabinet->s.eType != ET_CABINET_H) return qfalse;
		amount = item->item->quantity;
	} else if(item->item->giTag == WP_AMMO) {
		if(cabinet->s.eType != ET_CABINET_A) return qfalse;
		amount = item->count;
	} else return qfalse;
	for(i = 0; i < level.num_entities; ++i) {
		gentity_t *trigger = &g_entities[i];
		if(!trigger->target_ent || trigger->target_ent->s.number != cabinet->s.number)
			continue;
		if(trigger->count == -9999 || trigger->count <= trigger->health)
			return qfalse;
		/* Original signed32 addition followed by a signed upper clamp. */
		{
			unsigned int sum = (unsigned int)trigger->health + (unsigned int)amount;
			int health = sum <= INT_MAX ? (int)sum : -1 - (int)(UINT_MAX - sum);
			trigger->health = health < trigger->count ? health : trigger->count;
		}
		G_FreeEntity(item);
		return qtrue;
	}
	return qfalse;
}

/*
================
G_RunItem

================
*/
void G_RunItem( gentity_t *ent ) {
	vec3_t		origin;
	trace_t		tr;
	int			contents;
	int			mask;

	// if groundentity has been set to -1, it may have been pushed off an edge
	if ( ent->s.groundEntityNum == -1 ) {
		if ( ent->s.pos.trType != TR_GRAVITY ) {
			ent->s.pos.trType = TR_GRAVITY;
			ent->s.pos.trTime = level.time;
		}
	}

	if(ent->s.pos.trType == TR_GRAVITY_PAUSED) {
		vec3_t below;
		VectorCopy(ent->r.currentOrigin, below); below[2] -= 8.f;
		trap_Trace(&tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs,
			below, ent->s.number, ent->clipmask ? ent->clipmask : MASK_SOLID);
		if(tr.fraction > .5f && !tr.startsolid) {
			VectorClear(ent->s.pos.trDelta);
			ent->s.pos.trType = TR_GRAVITY;
			ent->s.pos.trTime = level.time;
		}
		G_RunThink(ent);
		return;
	}
	if(ent->s.pos.trType == TR_STATIONARY) {
		G_RunThink(ent);
		return;
	}

    if ( ent->s.pos.trType == TR_LINEAR && ( !ent->clipmask && !ent->r.contents ) ) {
        // check think function
        G_RunThink( ent );
        return;
    }

	// get current position
	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin, qfalse, ent->s.effect2Time );

	/* Original G_RunItem (ELF 0x75810): all moving items transition
	 * between water and air; the damage/knife checks occur afterwards. */
	{
		trace_t liquid;
		trap_Trace(&liquid, ent->r.currentOrigin, ent->r.mins, ent->r.maxs,
			origin, ent->r.ownerNum, MASK_WATER);
		if(liquid.fraction == 1.f && !liquid.startsolid &&
		   !(trap_PointContents(ent->r.currentOrigin, -1) & MASK_WATER)) {
			if(ent->s.pos.trType != TR_GRAVITY) {
				VectorCopy(origin, ent->s.pos.trBase);
				ent->s.pos.trType = TR_GRAVITY;
				ent->s.pos.trTime = level.time;
			}
		} else if(ent->s.pos.trType != TR_GRAVITY_FLOAT) {
			VectorCopy(liquid.endpos, ent->s.pos.trBase);
			ent->s.pos.trType = TR_GRAVITY_FLOAT;
			ent->s.pos.trTime = level.time;
			VectorScale(ent->s.pos.trDelta, .125f, ent->s.pos.trDelta);
			VectorScale(ent->s.apos.trDelta, .125f, ent->s.apos.trDelta);
		}
	}

	// trace a line from the previous position to the current position
	if ( ent->clipmask ) {
		mask = ent->clipmask;
	} else {
		mask = MASK_SOLID;
	}
	if(ent->damage && ent->parent) {
		qboolean linked = ent->parent->r.linked;
		ent->parent->r.linked = qfalse;
		trap_Trace(&tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs,
			origin, ent->s.number, mask);
		ent->parent->r.linked = linked;
	} else {
		trap_Trace(&tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs,
			origin, ent->r.ownerNum, mask);
	}

	if (ent->isProp && ent->takedamage)
	{
		G_RunItemProp (ent, origin);
	}
	
	VectorCopy( tr.endpos, ent->r.currentOrigin );

	if ( tr.startsolid ) {
		tr.fraction = 0;
	}

	trap_LinkEntity( ent );	// FIXME: avoid this for stationary?

	// check think function
	G_RunThink( ent );

	if ( tr.fraction == 1 ) {
		return;
	}

	if(tr.entityNum >= 0 && tr.entityNum < MAX_GENTITIES &&
	   G_NITMOD_CheckForCabinetResupply(ent, &g_entities[tr.entityNum]))
		return;

	// if it is in a nodrop volume, remove it
	contents = trap_PointContents( ent->r.currentOrigin, -1 );
	if ( contents & CONTENTS_NODROP ) {
		if (ent->item && ent->item->giType == IT_TEAM) {
			Team_ReturnFlag(ent, NULL);
		} else {
			G_FreeEntity( ent );
		}
		return;
	}

	/* Original 0x75ac2..0x75dc0: flying items deal speed-dependent impact
	 * damage above 300 units/s. The item remains available for pickup. */
	if(ent->damage && tr.entityNum >= 0 && tr.entityNum < ENTITYNUM_NONE) {
		gentity_t *hit = &g_entities[tr.entityNum];
		vec3_t velocity, direction;
		float speed;
		/* Original x87 calculation converts only after adding previousTime. */
		int hitTime = (int)(level.previousTime + (level.time-level.previousTime)*(double)tr.fraction);
		BG_EvaluateTrajectoryDelta(&ent->s.pos, hitTime, velocity, qfalse, ent->s.effect2Time);
		VectorCopy(velocity, direction);
		VectorNormalize(direction);
		speed = VectorLength(velocity);
		if(speed > 300.f && hit->takedamage) {
			if((g_friendlyFire.integer & 1) || g_gametype.integer == GT_WOLF_DM ||
			   !ent->parent || !OnSameTeam(ent->parent, hit))
				G_Damage(hit, ent, ent->parent, direction, tr.endpos,
					/* Keep intermediates wide until the integer conversion, as in
					 * the original x87 path (0x75b81..0x75bb9). */
					(int)(((double)speed-300.0)/20.0 + ent->damage), 0, ent->methodOfDeath);
			if(hit->client && hit->takedamage) {
				gentity_t *impact = G_NITMOD_TempEvent(tr.endpos, EV_MISSILE_HIT);
				impact->s.otherEntityNum = hit->s.number;
				impact->s.weapon = ent->s.weapon;
				impact->s.clientNum = ent->r.ownerNum;
			}
		}
	}
	G_BounceItem( ent, &tr );
}
