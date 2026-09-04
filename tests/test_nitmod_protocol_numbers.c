#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "nitmod_protocol.h"

#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    const char *invalid[] = { "", "-1", "+1", " 1", "1 ", "1xyz", "1 1023",
        "0x10", "1.5", "1e3", "1\n", "99999999999999999999999999999999999" };
    int i;
    int signedValue;
    unsigned int unsignedValue;
    char boundary[64];
    char encoded[32], decoded[64];
    char byteText[2], commandText[1024];
    const char *chatNames[] = {"say", "say_team", "say_teamnl", "say_buddy", "ma", "m", "pm"};
    for (i = 1; i <= 255; ++i) {
        byteText[0] = (char)i; byteText[1] = 0;
        CHECK(NITMOD_EncodeText(byteText, encoded, sizeof(encoded)));
        CHECK(NITMOD_TextNeedsEncoding(byteText) == (i == '%' || i == '=' || i >= 127));
        NITMOD_DecodeText(encoded);
        CHECK(!strcmp(byteText, encoded));
        CHECK(NITMOD_BuildChatCommand("say", byteText, commandText, sizeof(commandText)) == (i >= 32 && i != '"'));
    }
    for (i = 0; i < 7; ++i) {
        CHECK(!strcmp(NITMOD_ChatCommand(chatNames[i]), chatNames[i]));
        CHECK(NITMOD_BuildChatCommand(chatNames[i], "name hello %=", commandText, sizeof(commandText)));
        sprintf(decoded, "%s \"name hello =25=3D\"\n", chatNames[i]);
        CHECK(!strcmp(commandText, decoded));
    }
    CHECK(!strcmp(NITMOD_ChatCommand("SaY_TeAmNL"), "say_teamnl"));
    CHECK(!NITMOD_ChatCommand("say;quit"));
    CHECK(!NITMOD_ChatCommand("say_team_extra"));
    CHECK(!NITMOD_ChatCommand(NULL));
    CHECK(!NITMOD_TextNeedsEncoding(NULL));
    strcpy(commandText, "unchanged");
    CHECK(!NITMOD_BuildChatCommand("say", "%", commandText, 10));
    CHECK(!strcmp(commandText, "unchanged"));
    CHECK(NITMOD_BuildChatCommand("say", "%", commandText, 11));
    CHECK(!strcmp(commandText, "say \"=25\"\n"));
    strcpy(commandText, "unchanged");
    CHECK(!NITMOD_BuildChatCommand("say", "bad\nquit", commandText, sizeof(commandText)));
    CHECK(!strcmp(commandText, "unchanged"));
    CHECK(!NITMOD_BuildChatCommand("say", "bad\"quit", commandText, sizeof(commandText)));
    CHECK(!NITMOD_BuildChatCommand("quit", "x", commandText, sizeof(commandText)));
    CHECK(!NITMOD_BuildChatCommand("say", "", commandText, sizeof(commandText)));
    CHECK(NITMOD_EncodeText("%=\xC3\xA4", encoded, sizeof(encoded)));
    CHECK(!strcmp(encoded, "=25=3D=C3=A4"));
    NITMOD_DecodeText(encoded);
    CHECK(!strcmp(encoded, "%=\xC3\xA4"));
    strcpy(encoded, "unchanged");
    CHECK(!NITMOD_EncodeText("%", encoded, 3));
    CHECK(!strcmp(encoded, "unchanged"));
    CHECK(NITMOD_EncodeText("%", encoded, 4));
    strcpy(decoded, "=00=1F=2f=GG=== =3D25=20=FF");
    NITMOD_DecodeText(decoded);
    CHECK(!strcmp(decoded, "=00=1F=2f=GG=== =25 \xFF"));
    strcpy(decoded, "=2"); NITMOD_DecodeText(decoded);
    CHECK(!strcmp(decoded, "=2"));
    strcpy(decoded, "="); NITMOD_DecodeText(decoded);
    CHECK(!strcmp(decoded, "="));
    CHECK(!NITMOD_EncodeText(NULL, encoded, sizeof(encoded)));
    CHECK(!NITMOD_EncodeText("x", NULL, 4));
    NITMOD_DecodeText(NULL);
    for( i = 0; i < (int)( sizeof(invalid) / sizeof(invalid[0]) ); i++ ) {
        signedValue = 77;
        unsignedValue = 77;
        CHECK( !NITMOD_ParseProtocolInteger( invalid[i], &signedValue ) );
        CHECK( !NITMOD_ParseProtocolUnsigned( invalid[i], &unsignedValue ) );
        CHECK( signedValue == 77 && unsignedValue == 77 );
    }
    CHECK( !NITMOD_ParseProtocolInteger( NULL, &signedValue ) );
    CHECK( !NITMOD_ParseProtocolUnsigned( NULL, &unsignedValue ) );
    CHECK( !NITMOD_ParseProtocolInteger( "1", NULL ) );
    CHECK( !NITMOD_ParseProtocolUnsigned( "1", NULL ) );
    CHECK( NITMOD_ParseProtocolInteger( "000654", &signedValue ) && signedValue == 654 );
    CHECK( NITMOD_ParseProtocolUnsigned( "0", &unsignedValue ) && unsignedValue == 0 );
    sprintf( boundary, "%d", INT_MAX );
    CHECK( NITMOD_ParseProtocolInteger( boundary, &signedValue ) && signedValue == INT_MAX );
    sprintf( boundary, "%u", (unsigned int)INT_MAX + 1u );
    CHECK( !NITMOD_ParseProtocolInteger( boundary, &signedValue ) && signedValue == INT_MAX );
    CHECK( NITMOD_ParseProtocolUnsigned( boundary, &unsignedValue ) );
    sprintf( boundary, "%u", UINT_MAX );
    CHECK( NITMOD_ParseProtocolUnsigned( boundary, &unsignedValue ) && unsignedValue == UINT_MAX );
    sprintf( boundary, "%u0", UINT_MAX );
    CHECK( !NITMOD_ParseProtocolUnsigned( boundary, &unsignedValue ) && unsignedValue == UINT_MAX );
    sprintf( boundary, "%u", NITMOD_FEATURES_CLIENT );
    CHECK( NITMOD_ParseProtocolUnsigned( boundary, &unsignedValue ) && unsignedValue == NITMOD_FEATURES_CLIENT );
    return 0;
}
