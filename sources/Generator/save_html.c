/* save_html.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "save_html.h"

#define PLAIN_SUDOKU    0
#define SYMBOLIC_SUDOKU 1
#define IMAGE_SUDOKU    2

#define SUDOKU_TYPE PLAIN_SUDOKU

void save_html(char *puzzle, int seed, char *suffix) {
  char *header_1 =
      "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" "
        "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
      "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
      "<head>\n"
      "<title>"
      ;
  char *header_2 =
      "</title>\n"
      "<meta http-equiv=\"Content-type\" "
        "content=\"text/html;charset=UTF-8\"/>\n"
      "<style type=\"text/css\">\n"
      "table {empty-cells:show; border-collapse:collapse;}\n"
      "td {\n"
      "  width:50px; height:50px;\n"
      "  border-style:solid; border-width:1px; border-color:#000000;\n"
      "  text-align:center; vertical-align:middle;\n"
      "  font-family:Arial, Verdana, Sans-serif; font-size:2em;\n"
      "  }\n"
      ".c0 {border-top-width:3px; border-left-width:3px;}\n"
      ".c1 {border-top-width:3px;}\n"
      ".c2 {border-top-width:3px; border-right-width:3px;}\n"
      ".c3 {border-left-width:3px;}\n"
      ".c4 {}\n"
      ".c5 {border-right-width:3px;}\n"
      ".c6 {border-bottom-width:3px; border-left-width:3px;}\n"
      ".c7 {border-bottom-width:3px;}\n"
      ".c8 {border-bottom-width:3px; border-right-width:3px;}\n"
      "</style>\n</head>\n<body>\n<table>\n"
      ;
  char *footer = "</table>\n</body>\n</html>";

  char f_name[64] = {0};
  sprintf(f_name, "%d%s.html", seed, suffix);

  FILE *fp = fopen(f_name, "w");
  if (fp == NULL) {
    printf("Unable to open the file '%s' for writing\n", f_name);
    }
  else {
    fprintf(fp, "%s%d%s", header_1, seed, header_2);
    for (int i = 0; i < 81; i++) {
      int kR = i / 9;
      int kC = i - kR * 9;
      if (kC == 0) fprintf(fp, "<tr>");

#if SUDOKU_TYPE == PLAIN_SUDOKU
      fprintf(fp, "<td class=\"c%d\">%c</td>",
          kR % 3 * 3 + kC % 3, ((puzzle[i] == '0') ? ' ' : puzzle[i])
          );
#elif SUDOKU_TYPE == SYMBOLIC_SUDOKU
      char *symbols[10] = {"", "\u260E", "\u2622", "\u262F", "\u263C", "\u263D",
          "\u2658", "\u269B", "\u2665", "\u266B"
          };

      fprintf(fp, "<td class=\"c%d\">%s</td>",
          kR % 3 * 3 + kC % 3, symbols[(int)(puzzle[i] - '0')]
          );
#elif SUDOKU_TYPE == IMAGE_SUDOKU
      fprintf(fp, "<td class=\"c%d\" background=\"%c.jpg\"> </td>",
          kR % 3 * 3 + kC % 3, puzzle[i]
          );
#endif

      if ((kC + 1) % 3 == 0) fprintf(fp, "\n");
      if (kC == 8) fprintf(fp, "</tr>\n");
      }
    fprintf(fp, "%s\n", footer);
    fclose(fp);
    }
  }
