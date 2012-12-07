#ifndef CMD_HDR
#define CMD_HDR "$"
#endif

enum cmd_type {
    PID_CMD,
    SERVO_CMD,
    UNKNOWN_CMD
};

typedef struct cmd {
    unsigned char header[sizeof(CMD_HDR)];
    enum cmd_type type;
    unsigned char key[3];
    unsigned char value[7];
} cmd_t;

void cmd_execute(char *);
unsigned char cmd_parse(char *);