#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#define BUFFER 20
#define GUID_LEN 4

typedef struct{
    char name[BUFFER];
    int hp;
} PLAYER_STATUS;

typedef struct{
    char guid[GUID_LEN+1];
    int (*read)(PLAYER_STATUS *player);
    int (*write)(const PLAYER_STATUS *player);
} SAVE_FILE_PROTOCOL;

typedef struct{
    char guid[GUID_LEN+1];
    int (*get_protocol)(const char *guid,void **protocol);
    int (*get_guid)(const char *guid,void *protocol);
} LOCATE_PROTOCOL;

#endif
