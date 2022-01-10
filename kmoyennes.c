#include "kmoyennes.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "image.h"

int main(int argc, const char** argv) {
  Image im;
  int k;
  const char* f;
  time_t t;
  srand((unsigned)time(&t));

  if (argc < 2) {
    fprintf(stderr, "Usage: %s image [k]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  f = argv[1];
  k = (argc < 3) ? 3 : atoi(argv[2]);
  (void)k;  // cette ligne permet d'éviter un warning indiquant que la
            // variable $k$ n'est pas utilisée. À retirer.

  im_init(&im, f);  // construit l'image à partir d'un fichier
  black_white_image(&im);

  im_write(&im, "out.ppm");
  im_free(&im);

  return 0;
}

bool is_dark(Color col) { return col.r + col.g + col.b < 382; }

bool same_k(Color* old, Color* new, int k) {
  int i;
  for (i = 0; i < k; ++i) {
    if (old[i].r != new[i].r || old[i].g != new[i].g || old[i].b != new[i].b) {
      return false;
    }
  }
  return true;
}

// k_means clustering algorithm
void k_means(Image* im, int k) {
  Color random_colors[k];
  // Pick k random colors in the image
  for (int i = 0; i < k; i++) {
    Coord c = {rand() % im->w, rand() % im->h};
    random_colors[i] = im_get(im, c);
  }

  Color old_k_mean[k];
  Color new_k_mean[k];

  Coord k_pixel[k][im->w * im->h];
  int k_pixel_count[k];

  do {
    // Set new to old
    for (int i = 0; i < k; i++) {
      old_k_mean[i] = new_k_mean[i];
    }

    for (int i = 0; i < im->h * im->w; i++) {
      int diff = 255 * 255 * 3 + 1;
      int closest_k = 0;
      for (int j = 0; j < k; j++) {
        int new_diff = Color_diff(im->data[i], random_colors[j]);
        if (new_diff < diff) {
          diff = new_diff;
          closest_k = j;
        }
      }
      Coord c = {i % im->w, i / im->w};
      k_pixel[closest_k][k_pixel_count[closest_k]] = c;
      k_pixel_count[closest_k]++;
    }

    for (int i = 0; i < k; i++) {
      int r = 0;
      int g = 0;
      int b = 0;
      for (int j = 0; j < k_pixel_count[i]; j++) {
        Color c = im_get(im, k_pixel[i][j]);
        r += c.r;
        g += c.g;
        b += c.b;
      }
      r /= k_pixel_count[i];
      g /= k_pixel_count[i];
      b /= k_pixel_count[i];
      new_k_mean[i] = (Color){r, g, b};
    }
    // reset k_pixel_count
    for (int i = 0; i < k; i++) {
      k_pixel_count[i] = 0;
    }
  } while (!same_k(old_k_mean, new_k_mean, k));
}

void black_white_image(Image* im) {
  ImageIterator iter;
  Coord c;
  iter_init(im, &iter);

  while (!iter_ended(im, &iter)) {
    c = iter_next(im, &iter);
    Color color = im_get(im, c);
    if (is_dark(color)) {
      im_set(im, c, black);
    } else {
      im_set(im, c, white);
    }
  }
}
