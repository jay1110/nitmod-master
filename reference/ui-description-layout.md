# Description panels: shared typed renderer

UI_DrawCampaignDescription and UI_DrawGametypeDescription are mapped from
ui_ui_draw.c (decompiled function prologues around 0x2e509 and 0x2e909).
The original selects campaign/map/LMS text via ui_netGameType and the local
or network map index, substitutes `^1No text supplied`, and uses different
explicit break markers: single star for campaign text, double star for mode
descriptions. Their baseline starts at rect.y, not text_y. These choices are
retained, including using ui_netGameType for both local and network panels.

The three production consumers, including the native campaign-region panel,
now share UI_DrawDescriptionText in ui_nitmod_description.c. Last-word wrap,
left/center/right alignment, newline handling, carriage-return replacement and
five-pixel leading remain. The region panel retains its text_y baseline and
unlock/progress checks. No menu, briefing or PK3 asset is edited.

Hardening differences are explicit: the 1024-byte line buffer is bounded,
long unbroken words are emitted in bounded chunks rather than overflowing;
zero/negative widths or scales produce no draw. Invalid counts/indices and
missing region pointers cannot index the catalog. Invalid campaign selection
uses unavailable text without rewriting user cvars during rendering. Region
indices must also be inside the campaign's actual mapCount. These are not
claims of byte-exact malformed-input parity.

The full UI-link test uses display-context callbacks to verify drawn text,
coordinates, all three break modes and alignments, ordinary word wrapping,
4096-byte words, campaign/LMS/map selection, gametype paragraphs and region
indices -1 through MAX_MAPS_PER_CAMPAIGN. Existing rendered font code is
unchanged; callbacks resolve to the same UI text services in production.
Real browser screenshot comparison and complete original UI parity remain open.
