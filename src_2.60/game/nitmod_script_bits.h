#ifndef NITMOD_SCRIPT_BITS_H
#define NITMOD_SCRIPT_BITS_H

/* Original i386 script shifts use the low five bits of the bit number. */
static unsigned int NITMOD_ScriptBitMask(int bit) {
    return 1u << ((unsigned int)bit & 31u);
}

#endif
