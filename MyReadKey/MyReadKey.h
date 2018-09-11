#ifndef H_MyReadKey
#define H_MyReadKey
enum keys {l, s, r, t, i, f5, f6, enter, up, down, lft, rght};
int rk_readkey (enum keys *key);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
#endif