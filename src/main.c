#include <stdio.h>
#include <curses.h>
#include <locale.h>
#include <string.h>
#include "stack.h"
#include "path.h"

int redrawscreen(WINDOW* bottom){
  wnoutrefresh(stdscr);
  wnoutrefresh(bottom);
  doupdate();
  return 0;
}

int bottombardraw(WINDOW* bar){
  wmove(bar, 0, 0);
  wprintw(bar, "\u2193 scroll down\t\u2191 scroll up\tq quit");
  return 0;
}

enum colorstate {
  CYAN,
  YELLOW,
  GREEN,
  MAGENTA,
  RED
};

int writetext(char* buf, size_t size){
  int state = -1;
  int row = 0;
  int col = 0;
  for (size_t i = 0; i < size; i++) {
    if(col >= COLS){
      row++;
      col = 0;
    }
    if(row >= LINES-1){
      return i;
    }
    if(buf[i] == '\n'){
      row++;
      col = 0;
      continue;
    }

    if (buf[i] == '\x1b') {
      if(state != -1){
        wattroff(stdscr,COLOR_PAIR(state + 1));
        state = -1;
        i++;
        continue;
      }
      i++;
      state = buf[i] - '0';
      wattron(stdscr, COLOR_PAIR(state +1));
      continue;
    }
    mvaddch(row, col, buf[i]);
    col++;
  }
  return size;
}

int getviewsize(char* buf, size_t size, int viewport){
  int row = 0;
  int col = 0;
  for(size_t i = viewport; i < size; i++){
    if(col >= COLS){
      row++;
      col = 0;
    }
    if(row >= LINES-1){
      return i-viewport;
    }
    if(buf[i] == '\n'){
      row++;
      col = 0;
      continue;
    }
    col++;
  }
  return size-viewport;
}

int main(int argc, char** argv){
  setlocale(LC_ALL, "");
  if(argc < 2){
    printf("Too little arguments supplied\nUsage: sdoc 'path/to/document/under/usr/share/sdoc'\n");
    return -1;
  }
  char *file;
  ssize_t filesize = load_doc(argv[1], &file);
  if(filesize < 0 ){
    printf("Error loading document, %ld", filesize);
    return -1;
 }

 initscr();
 if (has_colors() == FALSE) {
   endwin();
   printf("Your terminal does not support color\n");
   return -1;
   ;
 }
  start_color();
  use_default_colors();
  init_pair(1, COLOR_CYAN, -1);
  init_pair(2,COLOR_YELLOW, -1);
  init_pair(3, COLOR_GREEN, -1);
  init_pair(4, COLOR_MAGENTA, -1);
  init_pair(5, COLOR_RED, -1);
  
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  int height = LINES;
  int width = COLS;

  WINDOW *bottombar = newwin(1, width, height - 1, 0);
  bottombardraw(bottombar);

  redrawscreen(bottombar);
  int inp;
  int viewporti = 0;
  writetext(file, filesize);

  int stack[512];
  int stackp = -1;

  do {
    inp = getch();

    if (inp == KEY_DOWN) {
      int currentdrawn = getviewsize(file, filesize, viewporti);
      if (viewporti + currentdrawn == filesize)
        continue;
      push(stack, 512, &stackp, viewporti);
      viewporti += currentdrawn;
      werase(stdscr);
      writetext(file + viewporti, filesize - viewporti);
      bottombardraw(bottombar);
      redrawscreen(bottombar);
    }
    if (inp == KEY_UP) {
      if (stackp == -1)
        continue;
      viewporti = pop(stack, &stackp);
      werase(stdscr);
      writetext(file + viewporti, filesize - viewporti);
      bottombardraw(bottombar);
      redrawscreen(bottombar);
    }
  }
  while(inp != 'q');
  free(file);
  endwin();
  return 0;
}
