char *takeInput(void);
char **parseInput(char *input);
void execute(char **commands,int in,int out,int wait);
void help(void);
void pipelining(char **commands);
void welcome(void);
void builtIn(char **command,int in,int out);
