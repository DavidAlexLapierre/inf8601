#include <stdio.h>

#include "filter.h"
#include "pipeline.h"
#include "pthread.h"
#include <unistd.h>
#include <queue.h>

int should_stop = 0;

void load_image(image_dir_t* image_dir) {
    image_t* image = image_dir_load_next(image_dir);
    if (image == NULL) should_stop = 1;
    insert_image(image);
}

void double_image() {
    images[1] = filter_scale_up(images[1], 2);
}

void desaturate_image() {
    images[2] = filter_desaturate(images[2]);
}

void flip_image() {
    images[3] = filter_horizontal_flip(images[3]);
}

void sobel_filter() {
    images[4] = filter_sobel(images[4]);
}

void save_image(image_dir_t* image_dir) {
    image_dir_save(image_dir, images[5]);
}

int pipeline_pthread(image_dir_t* image_dir) {
    queue_t queue = queue_create(6);
    pthread_t double_id;
    pthread_t desat_id;
    pthread_t flip_id;
    pthread_t sobel_id;
    pthread_t save_id;

    queue_push(queue, (void*) load_image);
    queue_push(queue, (void*) double_image);
    queue_push(queue, (void*) desaturate_image);
    queue_push(queue, (void*) flip_image);
    queue_push(queue, (void*) sobel_filter);
    queue_push(queue, (void*) save_image);

    while (1) {
        // Load

        load_image(image_dir);
        if (images[1] != NULL) pthread_create(&double_id, NULL, (void*) &double_image, image_dir);
        if (images[2] != NULL) pthread_create(&desat_id, NULL, (void*) &desaturate_image, NULL);

        

        printf(".");
        fflush(stdout);

        if (should_stop && images[5] == NULL) break;

    }
    return 0;
}   