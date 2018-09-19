//Writes 80x25 screen. 2 bytes/item
void init_display(char *video) {
    unsigned int i = 0;
    while(i < 80*25*2) {
        //Blank char on grey background
        video[i] = ' ';
        video[i+1] = 0x07;
        i = i + 2;
    }
    return;
}

//Writes strings to display
void write_str(char *video, const char *msg) {
    unsigned int str_index = 0;
    unsigned int disp_index = 0;
    
    while(msg[str_index] != '\0') {
        video[disp_index] = msg[str_index];
        video[disp_index+1] = 0x07;
        ++str_index;
        disp_index = disp_index + 2;
    }
    return;
}

void kmain(void) {
    //hello world
    const char *msg = "ocean-os kernel";
    char *video = (char*)0xb8000;
    
    init_display(video);
    write_str(video, msg);
    return;
}

