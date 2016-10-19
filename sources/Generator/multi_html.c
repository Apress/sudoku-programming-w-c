/* multi_html.c
 *
 * This module must be able to display all different types of multi-grid
 * puzzles (only the boxes are shown):
 *
 * +---+---+---+
 * |   |   |   |
 * +---+---+---+
 * |   | 1 |   |
 * +---+---+---+---+---+         N_GRIDS == 2 (double Sudokus)
 * |   |   |   |   |   |
 * +---+---+---+---+---+
 *         |   | 0 |   |
 *         +---+---+---+
 *         |   |   |   |
 *         +---+---+---+
 *
 * +---+---+---+
 * |   |   |   |
 * +---+---+---+
 * |   | 1 |   |
 * +---+---+---+---+---+
 * |   |   |   |   |   |
 * +---+---+---+---+---+
 *         |   | 0 |   |           N_GRIDS == 3
 *         +---+---+---+---+---+
 *         |   |   |   |   |   |
 *         +---+---+---+---+---+
 *                 |   | 2 |   |
 *                 +---+---+---+
 *                 |   |   |   |
 *                 +---+---+---+
 *
 * +---+---+---+   +---+---+---+
 * |   |   |   |   |   |   |   |
 * +---+---+---+   +---+---+---+
 * |   | 1 |   |   |   | 3 |   |
 * +---+---+---+---+---+---+---+
 * |   |   |   |   |   |   |   |
 * +---+---+---+---+---+---+---+
 *         |   | 0 |   |           N_GRIDS == 4
 *         +---+---+---+---+---+
 *         |   |   |   |   |   |
 *         +---+---+---+---+---+
 *                 |   | 2 |   |
 *                 +---+---+---+
 *                 |   |   |   |
 *                 +---+---+---+
 *
 * +---+---+---+   +---+---+---+
 * |   |   |   |   |   |   |   |
 * +---+---+---+   +---+---+---+
 * |   | 1 |   |   |   | 3 |   |
 * +---+---+===+===+===+---+---+
 * |   |   I   |   |   I   |   |
 * +---+---+---+---+---+---+---+
 *         I   | 0 |   I           N_GRIDS == 5 (samurai)
 * +---+---+---+---+---+---+---+   (the central puzzle is highlighted)
 * |   |   I   |   |   I   |   |
 * +---+---+===+===+===+---+---+
 * |   | 4 |   |   |   | 2 |   |
 * +---+---+---+   +---+---+---+
 * |   |   |   |   |   |   |   |
 * +---+---+---+   +---+---+---+
 *
 * The cell borders are defined like in save_html.c, but their position
 * and the size of the HTML table depend on the type of puzzle.
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "in_box.h"
#include "multi_html.h"

// Define the number of rows and columns needed for the multi-grid
#if N_GRIDS == 2
#define SIZE 15
#else
#define SIZE 21
#endif

char multi_string[N_GRIDS][2][82];

// The following table identifies the box of each grid that overlaps with
// a corner box of grid 0 when creating multi-grid Sudokus.
//
// N_GRIDS  kPuz=1  kPuz=2  kPuz=3  kPuz=4
//     2      8
//     3      8       0
//     4      8       0       6
//     5      8       0       6       2
//
// Puzzle:               0  1  2  3  4
int overlapping_box[] = {0, 8, 0, 6, 2};

void multi_html(int seed, int what) {
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
      ".c_ {border-top-width:0px; border-right-width:0px; "
              "border-bottom-width:0px; border-left-width:0px;}\n"
      "</style>\n</head>\n<body>\n<table>\n"
      ;
  char *footer = "</table>\n</body>\n</html>";

  // Puzzle offsets (row/column) for each puzzle (puzzle 0 is in the middle):
  //                  0      1       2       3        4
  int offs[5][2] = {{6,6}, {0,0}, {12,12}, {0,12}, {12,0}};

  // Combined multi-string (+1 to be able to close each string with a '\0').
  char multi_s[SIZE][SIZE + 1];
  for (int k = 0; k < SIZE; k++) {
    for (int j = 0; j < SIZE; j++) {
      multi_s[k][j] = ' ';
      }
    multi_s[k][SIZE] = '\0';
    }

  // Copy the puzzles to the places they belong.
  // The boxes that overlap are set twice, first for puzzle 0 and then for
  // the other one. But it doesn't matter, as the two boxes are identical.
  // To set them only once, it would be sufficient to do the setting only
  // if (multi_s[baseR + kR][baseC + kC] == ' ')
  for (int kPuz = 0; kPuz < N_GRIDS; kPuz++) {
    int baseR = offs[kPuz][ROW];
    int baseC = offs[kPuz][COL];
    char *s = multi_string[kPuz][what];
    for (int i = 0; i < 81; i++) {
      int kR = i / 9;
      int kC = i - kR * 9;
      multi_s[baseR + kR][baseC + kC] = (s[i] == '0') ? '.' : s[i];
      }
    }
  for (int k = 0; k < SIZE; k++) printf("%s\n", multi_s[k]);
  printf("\n");

  // Finally, save the HTML to disk
  char f_name[64] = {0};
  sprintf(f_name, "%d_%d%c.html", seed, N_GRIDS, (what == SOL) ? 's' : 'p');
  FILE *fp = fopen(f_name, "w");
  if (fp == NULL) {
    printf("Unable to open the file '%s' for writing\n", f_name);
    }
  else {
    fprintf(fp, "%s%d%s", header_1, seed, header_2);
    for (int kRow = 0; kRow < SIZE; kRow++) {
      char *s = multi_s[kRow];
      fprintf(fp, "<tr>");
      for (int i = 0; i < SIZE; i++) {
        if (s[i] == ' ') {
          fprintf(fp, "<td class=\"c_\"> </td>");
          }
        else {
          fprintf(fp, "<td class=\"c%d\" style=\"background-color:%s\">%c</td>",
              kRow % 3 * 3 + i % 3,
              (what == SOL  ||  (s[i] == '.') ? "White" : "LightGray"),
              ((s[i] == '.') ? ' ' : s[i])
              );
          }
        }
      fprintf(fp, "</tr>\n");
      }
    fprintf(fp, "%s\n", footer);
    fclose(fp);
    }
  }
