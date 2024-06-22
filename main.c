#include<stdio.h>
#include<string.h>
#include"protocol.h"

int write_save_file(const PLAYER_STATUS *player);
int read_save_file(PLAYER_STATUS *player);
int locate_prot(const char *guid,void **protocol);

SAVE_FILE_PROTOCOL file_protocol={
    .guid="1000",
    .read=&read_save_file,
    .write=&write_save_file
};

LOCATE_PROTOCOL locate_protocol={
    .guid="1001",
    .get_protocol=&locate_prot
};

int main(void)
{
    PLAYER_STATUS player={"yano",67};
    SAVE_FILE_PROTOCOL *save_file;
    locate_protocol.locate("1000",(void **)&save_file);
    save_file->write(&player);
    return 0;
}

int write_save_file(const PLAYER_STATUS *player)
{
    char file_name[BUFFER+4];
    int status;
    FILE *fp;

    sprintf(file_name,"%s%s",player->name,".sve");
    fp=fopen(file_name,"wb");
    if(fp==NULL)
    {
        return 1;
    }
    status=fwrite(player,sizeof(*player),1,fp);
    if(status==0||status==EOF)
    {
        return 1;
    }
    fclose(fp);
    return 0;
}

int read_save_file(PLAYER_STATUS *player)
{
    FILE *fp;
    int status;
    char file_name[BUFFER+4];

    sprintf(file_name,"%s%s",player->name,".sav");
    fp=fopen(file_name,"rb");
    if(fp==NULL)
    {
        return 1;
    }
    status=fread(player,sizeof(*player),1,fp);
    if(status==0||status==EOF)
    {
        return 1;
    }

    fclose(fp);
    return 0;
}

int locate_prot(const char *guid,void **protocol)
{
    if(strcmp(guid,"1000")==0)
    {
        *protocol=&file_protocol;
        return 0;
    }else if(strcmp(guid,"1001")==0){
        *protocol=&locate_protocol;
        return 0;
    }else{
        *protocol=NULL;
        return 1;
    }
}
