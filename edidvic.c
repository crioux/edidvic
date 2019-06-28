#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"vic_timings.h"

enum MODE {
    MODE_UNKNOWN=0,
    MODE_VIC=1
};

const char *program_name;


void help(const char *section)
{
    if(section==NULL)
    {
        fprintf(stderr, "Usage: %s <command> [arguments]\n", program_name);
        fprintf(stderr, "  Commands: vic <vic id>\n");
    }
    else if(strcmp(section,"vic")==0)
    {
        fprintf(stderr, "Usage: %s vic <vic id>\n", program_name);
        fprintf(stderr, "  Print the CEA-861 mode information for a given VIC id\n");
    }
}

int command_vic(int argc, char **argv)
{
    if(argc != 1)
    {
        help("vic");
        return 1;
    }
    int vic = atoi(argv[0]);

    const struct drm_display_mode *vicline=NULL;
    if(vic>0 && vic<=127)
    {
        vicline = edid_cea_modes+vic;
    }
    else if (vic>=193 && vic<=219)
    {
        vicline = edid_cea_modes_193+(vic-193);
    }

    float framerate = (vicline->clock * 1000.0) / (vicline->htotal * vicline->vtotal);
    if(vicline->flags & DRM_MODE_FLAG_DBLCLK)
    {
        printf("  Pixel Clock: %d.%d MHz\n", vicline->clock/1000, vicline->clock % 1000);
        printf("   Frame Rate: %f Hz\n", framerate);
    }
    else
    {
        printf("  Pixel Clock: %d.%d MHz (*2 = %d.%d MHz)\n", 
            vicline->clock/1000, vicline->clock%1000,
            vicline->clock*2/1000, vicline->clock*2%1000);
        printf("   Frame Rate: %f Hz (*2 = %f Hz)\n", framerate, framerate*2.0);
    }
	printf("     H Active: %d\n", vicline->hdisplay);
	printf("H Front Porch: %d\n", vicline->hsync_start-vicline->hdisplay);
	printf("       H Sync: %d\n", vicline->hsync_end-vicline->hsync_start);
	printf(" H Back Porch: %d\n", vicline->htotal-vicline->hsync_end);
    printf("      H Total: %d\n", vicline->htotal);
	printf("     V Active: %d\n", vicline->vdisplay);
	printf("V Front Porch: %d\n", vicline->vsync_start-vicline->vdisplay);
	printf("       V Sync: %d\n", vicline->vsync_end-vicline->vsync_start);
	printf(" V Back Porch: %d\n", vicline->vtotal-vicline->vsync_end);
    printf("      V Total: %d\n", vicline->vtotal);
    printf("        Flags:%s%s%s%s%s%s",
        vicline->flags & DRM_MODE_FLAG_PHSYNC ? " +hsync" : " -hsync",
        vicline->flags & DRM_MODE_FLAG_PVSYNC ? " +vsync" : " -vsync",
        vicline->flags & DRM_MODE_FLAG_INTERLACE ? " +interlace" : "",
        vicline->flags & DRM_MODE_FLAG_DBLSCAN ? " +dblscan" : "",
        vicline->flags & DRM_MODE_FLAG_DBLCLK ? " +dblclk" : "",
        vicline->flags & DRM_MODE_FLAG_CSYNC ? (vicline->flags & DRM_MODE_FLAG_PCSYNC ? " +pcsync" : " -pcsync" ) : ""
    );

    return 0;
}

int main(int argc, char **argv)
{
    int opt, vic;
    enum MODE mode = MODE_UNKNOWN;
    program_name = argv[0];

    if(argc<=1)
    {
        help(NULL);
        return 1;
    }

    if(strcmp(argv[1],"vic")==0)
    {
        mode = MODE_VIC;
    }

    switch(mode)
    {
    case MODE_VIC:
        return command_vic(argc-2, argv+2);

    default:
        help(NULL);
    }
    return 1;
}