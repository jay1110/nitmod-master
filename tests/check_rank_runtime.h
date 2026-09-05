static int CheckRankRuntime(void) {
    static const int expected[] = {0,1,2,3,4,5,5,6,6,7,7,8,8,8,9,9,9,
        10,10,10,10,10,10,10,10,10,10,10,10};
    static gclient_t client;
    int code, rest, skill, total, cases = 1, errors = 0;
    memset(&client, 0, sizeof(client));
    for(skill = 0; skill < SK_NUM_SKILLS; ++skill) cases *= NUM_SKILL_LEVELS;
    for(code = 0; code < cases; ++code) {
        rest = code; total = 0; client.sess.rank = 10;
        for(skill = 0; skill < SK_NUM_SKILLS; ++skill) {
            int level = rest % NUM_SKILL_LEVELS;
            rest /= NUM_SKILL_LEVELS; total += level;
            client.sess.skillpoints[skill] = (float)skillLevels[level];
            client.sess.skill[skill] = 0; /* Real G_CalcRank must recompute XP levels. */
        }
        G_CalcRank(&client);
        if(client.sess.rank != expected[total]) ++errors;
        rest = code;
        for(skill = 0; skill < SK_NUM_SKILLS; ++skill) {
            if(client.sess.skill[skill] != rest % NUM_SKILL_LEVELS) ++errors;
            rest /= NUM_SKILL_LEVELS;
        }
    }
    G_CalcRank(NULL);
    if(errors) fprintf(stderr, "active rank: %d failures\n", errors);
    return errors;
}
