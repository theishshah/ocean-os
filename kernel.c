//gcc includes these
#include <stddef.h>
#include <stdint.h>

//check to ensure cross-compiler is being used
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif

//vga text buffer, using 80x25 default
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int curr_col = 0;
int curr_row = 0;

uint8_t term_color = 0x0F;

void init_disp(){
    for(int col = 0; col<VGA_COLS; col++){
        for(int row = 0; row<VGA_ROWS; row++){
            //init display with blank ' ' characters
            const size_t index = (VGA_COLS*row) + col;
            vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
        }
    }
}

void shift_disp(){
    for(int col = 0; col<VGA_COLS; col++){
        for(int row = 1; row<VGA_ROWS; row++){
            //shift rows up by 1
            const size_t index_prev = (VGA_COLS*(row-1)) + col;
            const size_t index_curr = (VGA_COLS*row) + col;
            vga_buffer[index_prev] = vga_buffer[index_curr];
        }
    }
    int last_row = VGA_ROWS -1;
    for(int col=0; col<VGA_COLS; col++){
        //set final row to be blank ' ' chars
        const size_t index = (VGA_COLS*last_row) + col;
        vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
    }
    curr_row = last_row;
}

void put_char(char c){
    if(c == '\n'){
        curr_col = 0;
        curr_row++;
    }
    else{
        const size_t index = (VGA_COLS * curr_row) + curr_col;
        vga_buffer[index] = ((uint16_t)term_color << 8) | c;
        curr_col++;
    }

    if(curr_col >= VGA_COLS){
        curr_col = 0;
        curr_row++;
    }

    if(curr_row >= VGA_ROWS){
        curr_col = 0;
        shift_disp();
    }
}

size_t str_len(const char* str){
    size_t len = 0;
    while(str[len] != '\0'){
        len++;
    }
    return len;
}

void put_str(const char* str){
    for(size_t i = 0; i<str_len(str); i++){
        put_char(str[i]);
    }
}

void kernel_main(){
    init_disp();

    put_str("Welcome to Ish's kernel.\n");
}